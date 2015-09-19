#define  SIGNATURE_000 0x1e
#define  SIGNATURE_001 0x93
#define  SIGNATURE_002 0x07
#define  BOOTRST 0	// Select Reset Vector
#define  BOOTSZ0 1	// Select Boot Size
#define  BOOTSZ1 2	// Select Boot Size
#define  FLASHEND 0x0fff	// Note: Word address
#define  SRAM_START 0x0060
#define  SRAM_SIZE 1024
; ***** BOOTLOADER DECLARATIONS ******************************************
#define  PAGESIZE 32
#define  FIRSTBOOTSTART 0xf80
#define  SECONDBOOTSTART 0xf00
#define  THIRDBOOTSTART 0xe00
#define  FOURTHBOOTSTART 0xc00
#define  SMALLBOOTSTART FIRSTBOOTSTART
#define  LARGEBOOTSTART FOURTHBOOTSTART
