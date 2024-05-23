#define DEBUG 1
#include <stdio.h>
#include <termio.h>
#include <time.h>
#include <math.h>
#include <curses.h>
#define DSM_HOST "gltMandC"
#define DSM_SUCCESS 0
#define MICRODEG_TO_ARCSEC 0.0036

void receiversPage(int count) {
  time_t timestamp,system_time;
  char timeString[26];
  float seconds;
  struct tm* systemTime;
  int dsm_status;

  float power_4_9_caba4_lhc,power_4_9_caba4_rhc;
  float power_4_9_caba5_lhc,power_4_9_caba5_rhc;
  double rfSynthFreq=0.0,rfSynthPower=0.0,rfFinalLO=0.0;
  float rfCaba4VGAgain_lhc,rfCaba4VGAgain_rhc;
  float rfCaba5VGAgain_lhc,rfCaba5VGAgain_rhc;
  float rfCryostatColdhead,rfCryostatPlate4K;
  float rfCryostatPlate15K,rfCryostatPlate100;
  float rfCryostatAmbTemp;
  char c3String[3];
  char c1String[1];
  double volts;
  char pwrCaba4Timestamp[15];
  char pwrCaba5Timestamp[15];
  char rfCaba1Rcvr[3];
  char rfCaba1Toneval[1];
  char rfCaba1Tone[3];
  char rfCaba1Valon[1];
  char rfCaba1ValonLock[3];
  char rfCaba1FloogLock[3];
  char rfCaba11Rcvr[3];
  char rfCaba11Pol[3];
  char rfCaba11Sb[3];
  char rfCaba11Cont[3];
  char rfCaba11_595G[3];
  char rfCaba3AttLevel[3];
  char rfCaba4Rcvr[3];
  char rfCaba5Rcvr[3];
  char rfLoadval[10];
  char rfTimestamp[15];

  if ((count % 20) == 1) {
    /*
      Initialize Curses Display
    */
    initscr();
    clear();
    move(1,1);
    refresh();
  }

  move(0,0);
  system_time=time(NULL);
  move(1,10);
  printw("Receivers data at time: %s ",ctime(&system_time));


  dsm_status = dsm_read(DSM_HOST,"DSM_POWER_4_9_CABA4_LHC_F",&power_4_9_caba4_lhc,&timestamp); 
  dsm_status = dsm_read(DSM_HOST,"DSM_POWER_4_9_CABA4_RHC_F",&power_4_9_caba4_rhc,&timestamp); 
  dsm_status = dsm_read(DSM_HOST,"DSM_POWER_4_9_CABA5_LHC_F",&power_4_9_caba5_rhc,&timestamp);       
  dsm_status = dsm_read(DSM_HOST,"DSM_POWER_4_9_CABA5_RHC_F",&power_4_9_caba5_rhc,&timestamp);      
  dsm_status = dsm_read(DSM_HOST,"DSM_PWR_CABA4_TIMESTAMP_C15",pwrCaba4Timestamp,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_PWR_CABA5_TIMESTAMP_C15",pwrCaba5Timestamp,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_SYNTH_FREQ_D",&rfSynthFreq,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_SYNTH_POWER_D",&rfSynthPower,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_FINAL_LO_D",&rfFinalLO,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_RECEIVER_C3",rfCaba1Rcvr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_TONEVAL_C1",rfCaba1Toneval,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_TONE_C3",rfCaba1Tone,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_VALON_C1",rfCaba1Valon,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_VALON_LOCK_C3",rfCaba1ValonLock,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA1_FLOOG_LOCK_C3",rfCaba1FloogLock,&timestamp);

  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA11_RECEIVER_C3",rfCaba11Rcvr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA11_POL_C3",rfCaba11Pol,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA11_SB_C3",rfCaba11Sb,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA11_CONT_C3",rfCaba11Cont,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA11_595G_C3",rfCaba11_595G,&timestamp);

  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA3_ATTLEVEL_C3",rfCaba3AttLevel,&timestamp);

  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA4_RECEIVER_C3",rfCaba4Rcvr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA4_VGAGAIN_LHC_F",&rfCaba4VGAgain_lhc,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA4_VGAGAIN_RHC_F",&rfCaba4VGAgain_rhc,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA5_RECEIVER_C3",rfCaba5Rcvr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA5_VGAGAIN_LHC_F",&rfCaba5VGAgain_lhc,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CABA5_VGAGAIN_RHC_F",&rfCaba5VGAgain_rhc,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CRYOSTAT_COLDHEAD_F",&rfCryostatColdhead,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CRYOSTAT_PLATE4K_F",&rfCryostatPlate4K,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CRYOSTAT_PLATE15K_F",&rfCryostatPlate15K,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CRYOSTAT_PLATE100_F",&rfCryostatPlate100,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_RF_CRYOSTAT_AMBIENT_F",&rfCryostatAmbTemp,&timestamp);

  dsm_status = dsm_read(DSM_HOST,"DSM_RF_LOADVAL_C10",&rfLoadval,&timestamp);

  dsm_status = dsm_read(DSM_HOST,"DSM_RF_TIMESTAMP_C15",rfTimestamp,&timestamp);

  if (dsm_status != DSM_SUCCESS) {
  printf("Warning: DSM read failed! dsm_status=%d\n",dsm_status);
  }


  move(3,2);
  printBold("============== Tuning ==============");
  move(4,2);
  printLabel("Synth. Freq. (Hz):    ");printw("%12.2f",rfSynthFreq);
  /*printw("Synth. Freq. (Hz):    %12.2f",rfSynthFreq); */
  move(5,2);
  printLabel("Synth. Power (dBm):  ");printw("%12.6f",rfSynthPower);
  /*printw("Synth. Power (dBm):   %12.6f",rfSynthPower); */
  move(6,2);
  printLabel("WCA_Locked Freq(GHz): ");printw("%12.6f",rfFinalLO);
  move(7,2);
  printLabel("LO_PAD(63 is Max att):  ")

  move(9,2);
  printBold("========== Signal select ===========");
  move(10,2);
  printLabel("Receiver: ");printw("%s",rfCaba1Rcvr);
  move(11,2);
  printw("Sideband(for Tsys/Cont.Det ): %s",rfCaba1Toneval);
  move(12,2);
  printw("Polarization(for Phase monitor): %s",rfCaba1Toneval);


  move(14,2);
  printBold("======== Tone & Load Motor =========");
  move(15,2);
  printw("Tone Source: %s",rfCaba1Rcvr);
  move(16,2);
  printw("Tone Position: %s",rfCaba1Toneval);
  move(17,2);
  printw("LHC_Cont. Powwer(mv): %s",rfCaba1Toneval);
  move(18,2);
  printw("RHC_Cont. Powwer(mv): %s",rfCaba1Toneval);
  move(19,2);
  printw("PM#5_RHC/POL0(dBm) %s",rfCaba1Toneval);
  move(20,2);
  printw("PM#5_LHC/POL1(dBm) %s",rfCaba1Toneval);


  move(3,46);
  printAlt("====== Temp and Vacuum ======");
  move(4,46);
  printLab("Coldhead(K) :    ");printw("%4.1f",rfCryostatColdhead);
  move(5,46);
  printLab("4K_temp(K)  :    ");printw("%4.1f",rfCryostatPlate4K);
  move(6,46);
  printw("15K_temp(K) :    %4.1f ",rfCryostatPlate15K);
  move(7,46);
  printw("100K_temp(K):    %4.1f ",rfCryostatPlate100);
  move(8,46);
  printw("Ambient(K)  :    %4.1f ",rfCryostatAmbTemp);
  move(9,46);
  printw("Dewar_pressure:  %4.1f",rfCryostatAmbTemp);
  move(10,46);
  printw("Pump_pressure :  %4.1f",rfCryostatAmbTemp);

  move(13,46);
  printAlt("====== Various LO Status =======");
  move(14,46);
  printw("10MHz (5V Lock):  %s ",rfCaba1FloogLock);
  move(15,46);
  printw("31.5MHz_FLOOG (5V Lock): %s",rfCaba1FloogLock);
  move(16,46);
  printw("0.5/1.5GHz_Valon(3.5V lock): %s",rfCaba1ValonLock);
  move(17,46);
  printw("2.048GHz(5V Lock): %s",rfCaba1FloogLock);
  move(18,46);
  printw("3.85 GHz(5V Lock): %s",rfCaba1FloogLock);
  move(19,46);
  printw("8.15 GHz(5V Lock): %s",rfCaba1FloogLock);
  move(20,46);
  printw("5.95 GHz(5V Lock): %s",rfCaba1FloogLock);

  refresh();
}
