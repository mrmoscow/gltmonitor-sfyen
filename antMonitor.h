#define SOURCE_CHAR_LEN 34
#define HPDATA_LEN 512;
enum {ANTENNA_PAGE_CHECK_ONLY = 0, ANTENNA_PAGE_PRINT};
typedef struct {
  int flags;
  int timeDifferential;
  int azBrakeManualRelease;
  int estopBypass;
  int wackoOffsets;
  int driveTimeoutDisabled;
} ANTENNA_FLAGS;

