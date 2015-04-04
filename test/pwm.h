#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

// 15 DMA channels are usable on the RPi (0..14)
#define DMA_CHANNELS    15

// Standard page sizes
#define PAGE_SIZE       4096
#define PAGE_SHIFT      12

// Memory Addresses
#define DMA_BASE        0x20007000
#define DMA_CHANNEL_INC 0x100
#define DMA_LEN         0x24
#define PWM_BASE        0x2020C000
#define PWM_LEN         0x28
#define CLK_BASE        0x20101000
#define CLK_LEN         0xA8
#define GPIO_BASE       0x20200000
#define GPIO_LEN        0x100
#define PCM_BASE        0x20203000
#define PCM_LEN         0x24

// Datasheet p. 51:
#define DMA_NO_WIDE_BURSTS  (1<<26)
#define DMA_WAIT_RESP   (1<<3)
#define DMA_D_DREQ      (1<<6)
#define DMA_PER_MAP(x)  ((x)<<16)
#define DMA_END         (1<<1)
#define DMA_RESET       (1<<31)
#define DMA_INT         (1<<2)

// Each DMA channel has 3 writeable registers:
#define DMA_CS          (0x00/4)
#define DMA_CONBLK_AD   (0x04/4)
#define DMA_DEBUG       (0x20/4)

// GPIO Memory Addresses
#define GPIO_FSEL0      (0x00/4)
#define GPIO_SET0       (0x1c/4)
#define GPIO_CLR0       (0x28/4)
#define GPIO_LEV0       (0x34/4)
#define GPIO_PULLEN     (0x94/4)
#define GPIO_PULLCLK    (0x98/4)

// GPIO Modes (IN=0, OUT=1)
#define GPIO_MODE_IN    0
#define GPIO_MODE_OUT   1

// PWM Memory Addresses
#define PWM_CTL         (0x00/4)
#define PWM_DMAC        (0x08/4)
#define PWM_RNG1        (0x10/4)
#define PWM_FIFO        (0x18/4)

#define PWMCLK_CNTL     40
#define PWMCLK_DIV      41

#define PWMCTL_MODE1    (1<<1)
#define PWMCTL_PWEN1    (1<<0)
#define PWMCTL_CLRF     (1<<6)
#define PWMCTL_USEF1    (1<<5)

#define PWMDMAC_ENAB    (1<<31)
#define PWMDMAC_THRSHLD ((15<<8) | (15<<0))

#define PCM_CS_A        (0x00/4)
#define PCM_FIFO_A      (0x04/4)
#define PCM_MODE_A      (0x08/4)
#define PCM_RXC_A       (0x0c/4)
#define PCM_TXC_A       (0x10/4)
#define PCM_DREQ_A      (0x14/4)
#define PCM_INTEN_A     (0x18/4)
#define PCM_INT_STC_A   (0x1c/4)
#define PCM_GRAY        (0x20/4)

#define PCMCLK_CNTL     38
#define PCMCLK_DIV      39


int setup(int pw_incr_us, int hw);
void shutdown(void);
void set_loglevel(int level);

int init_channel(int channel, int subcycle_time_us);
int clear_channel(int channel);
int clear_channel_gpio(int channel, int gpio);
int print_channel(int channel);

int add_channel_pulse(int channel, int gpio, int width_start, int width);
char* get_error_message(void);
void set_softfatal(int enabled);

int is_setup(void);
int is_channel_initialized(int channel);
int get_pulse_incr_us(void);
int get_channel_subcycle_time_us(int channel);

#define DELAY_VIA_PWM   0
#define DELAY_VIA_PCM   1

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_ERRORS 1
#define LOG_LEVEL_DEFAULT LOG_LEVEL_DEBUG

// Default subcycle time
#define SUBCYCLE_TIME_US_DEFAULT 20000

// Subcycle minimum. We kept seeing no signals and strange behavior of the RPi
#define SUBCYCLE_TIME_US_MIN 3000

// Default pulse-width-increment-granularity
#define PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT 10
