#define DEBUG 1
#include <stdio.h>
#include <termio.h>
#include <time.h>
#include <math.h>
#include <curses.h>
#define DSM_HOST "gltacc"
#define DSM_SUCCESS 0
#define MICRODEG_TO_ARCSEC 0.0036

void metrologyPage(int count) {
  time_t timestamp,system_time;
  char timeString[26];
  float seconds;
  struct tm* systemTime;
  int dsm_status;
  int tilt1x,tilt1y,tilt2x,tilt2y,tilt3x,tilt3y;
  int tilt1Temp,tilt2Temp,tilt3Temp;
  int linearSensor1,linearSensor2,linearSensor3,linearSensor4;
  int tiltAzCorr,tiltElCorr;
  int linearSensorAzCorr,linearSensorElCorr;
  int SPEMazCorr,SPEMelCorr;
  short tempSensor[41];
  short azm1t,azm2t,elm1t,elm2t,elm3t,elm4t;

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
  move(1,5);
  printw("Metrology data at time: %s ",ctime(&system_time));

  dsm_status = dsm_read(DSM_HOST,"DSM_MET_TEMP_SENSOR_V41_S",tempSensor,&timestamp);
  if (dsm_status != DSM_SUCCESS) {
  printf("Warning: DSM write failed! DSM_MET_TEMP_SENSOR_V41_S dsm_status=%d\n",dsm_status);
  }

  dsm_status = dsm_read(DSM_HOST,"DSM_SPEM_AZCORR_L",&SPEMazCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_SPEM_ELCORR_L",&SPEMelCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR_AZCORR_L",&linearSensorAzCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR_ELCORR_L",&linearSensorElCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILTAZCORR_L",&tiltAzCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILTELCORR_L",&tiltElCorr,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR1_L",&linearSensor1,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR2_L",&linearSensor2,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR3_L",&linearSensor3,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_LINEAR_SENSOR4_L",&linearSensor4,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT1TEMP_L",&tilt1Temp,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT2TEMP_L",&tilt2Temp,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT3TEMP_L",&tilt3Temp,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT1X_L",&tilt1x,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT1Y_L",&tilt1y,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT2X_L",&tilt2x,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT2Y_L",&tilt2y,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT3X_L",&tilt3x,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_TILT3Y_L",&tilt3y,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_AZ_MOTOR1_TEMP_S",&azm1t,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_AZ_MOTOR2_TEMP_S",&azm2t,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_EL_MOTOR1_TEMP_S",&elm1t,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_EL_MOTOR2_TEMP_S",&elm2t,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_EL_MOTOR3_TEMP_S",&elm3t,&timestamp);
  dsm_status = dsm_read(DSM_HOST,"DSM_EL_MOTOR4_TEMP_S",&elm4t,&timestamp);


  move(3,5);
  printw("Tilt 1 X: %8.1f \"",(float)tilt1x * MICRODEG_TO_ARCSEC);
  move(3,35);
  printw("Tilt 1 Y: %8.1f \"",(float)tilt1y * MICRODEG_TO_ARCSEC);
  move(4,5);
  printw("Tilt 2 X: %8.1f \"",(float)tilt2x * MICRODEG_TO_ARCSEC);
  move(4,35);
  printw("Tilt 2 Y: %8.1f \"",(float)tilt2y * MICRODEG_TO_ARCSEC);
  move(5,5);
  printw("Tilt 3 X: %8.1f \"",(float)tilt3x * MICRODEG_TO_ARCSEC);
  move(5,35);
  printw("Tilt 3 Y: %8.1f \"",(float)tilt3y * MICRODEG_TO_ARCSEC);
  move(7,5);
  printw("Tiltmeter temperatures: (1): %5.1f C",(float)tilt1Temp/100.);
  move(7,44);
  printw("(2): %5.1f C",(float)tilt2Temp/100.);
  move(7,60);
  printw("(3): %5.1f C",(float)tilt3Temp/100.);
  move(8,0);
  printw("--------------------------------------------------------------------------------");
  move(9,5);
  printw("Linear sensors: (1) %5.1f     (2) %5.1f    (3) %5.1f    (4) %5.1f microns",
         (float)linearSensor1*0.1,
         (float)linearSensor2*0.1,
         (float)linearSensor3*0.1,
         (float)linearSensor4*0.1);
  move(10,0);
  printw("--------------------------------------------------------------------------------");
  move(11,5);
  printw("Tilt Az Correction: %d          Tilt El Correction: %d",tiltAzCorr,tiltElCorr);
  move(12,5);
  printw("SPEM Az Correction: %d          SPEM El Correction: %d",SPEMazCorr,SPEMelCorr);
  move(13,0);
  printw("--------------------------------------------------------------------------------");
  move(14,5);
  printw("Temperature sensors (C) (i x j) (i=1..6, j=1..6)");

  move(16,8);
  printw("1");
  move(16,21);
  printw("2");
  move(16,34);
  printw("3");
  move(16,46);
  printw("4");
  move(16,59);
  printw("5");
  move(16,72);
  printw("6");

  move(18,2);
  printw("1");
  move(18,7);
  printw("%5.1f",(float)tempSensor[0]/100.);
  move(18,20);
  printw("%5.1f",(float)tempSensor[1]/100.);
  move(18,33);
  printw("%5.1f",(float)tempSensor[2]/100.);
  move(18,45);
  printw("%5.1f",(float)tempSensor[3]/100.);
  move(18,58);
  printw("%5.1f",(float)tempSensor[4]/100.);
  move(18,71);
  printw("%5.1f",(float)tempSensor[5]/100.);

  move(20,2);
  printw("2");
  move(20,7);
  printw("%5.1f",(float)tempSensor[6]/100.);
  move(20,20);
  printw("%5.1f",(float)tempSensor[7]/100.);
  move(20,33);
  printw("%5.1f",(float)tempSensor[8]/100.);
  move(20,45);
  printw("%5.1f",(float)tempSensor[9]/100.);
  move(20,58);
  printw("%5.1f",(float)tempSensor[10]/100.);
  move(20,71);
  printw("%5.1f",(float)tempSensor[11]/100.);

  move(22,2);
  printw("3");
  move(22,7);
  printw("%5.1f",(float)tempSensor[12]/100.);
  move(22,20);
  printw("%5.1f",(float)tempSensor[13]/100.);
  move(22,33);
  printw("%5.1f",(float)tempSensor[14]/100.);
  move(22,45);
  printw("%5.1f",(float)tempSensor[15]/100.);
  move(22,58);
  printw("%5.1f",(float)tempSensor[16]/100.);
  move(22,71);
  printw("%5.1f",(float)tempSensor[17]/100.);

  move(24,2);
  printw("4");
  move(24,7);
  printw("%5.1f",(float)tempSensor[18]/100.);
  move(24,20);
  printw("%5.1f",(float)tempSensor[19]/100.);
  move(24,33);
  printw("%5.1f",(float)tempSensor[20]/100.);
  move(24,45);
  printw("%5.1f",(float)tempSensor[21]/100.);
  move(24,58);
  printw("%5.1f",(float)tempSensor[22]/100.);
  move(24,71);
  printw("%5.1f",(float)tempSensor[23]/100.);

  move(26,2);
  printw("5");
  move(26,7);
  printw("%5.1f",(float)tempSensor[24]/100.);
  move(26,20);
  printw("%5.1f",(float)tempSensor[25]/100.);
  move(26,33);
  printw("%5.1f",(float)tempSensor[26]/100.);
  move(26,45);
  printw("%5.1f",(float)tempSensor[27]/100.);
  move(26,58);
  printw("%5.1f",(float)tempSensor[28]/100.);
  move(26,71);
  printw("%5.1f",(float)tempSensor[29]/100.);

  move(28,2);
  printw("6");
  move(28,7);
  printw("%5.1f",(float)tempSensor[30]/100.);
  move(28,20);
  printw("%5.1f",(float)tempSensor[31]/100.);
  move(28,33);
  printw("%5.1f",(float)tempSensor[32]/100.);
  move(28,45);
  printw("%5.1f",(float)tempSensor[33]/100.);
  move(28,58);
  printw("%5.1f",(float)tempSensor[34]/100.);
  move(28,71);
  printw("%5.1f",(float)tempSensor[35]/100.);

  move(30,2);
  printw("7");
  move(30,7);
  printw("%5.1f",(float)tempSensor[36]/100.);
  move(30,20);
  printw("%5.1f",(float)tempSensor[37]/100.);
  move(30,33);
  printw("%5.1f",(float)tempSensor[38]/100.);
  move(30,45);
  printw("%5.1f",(float)tempSensor[39]/100.);
  move(30,58);
  printw("%5.1f",(float)tempSensor[40]/100.);
  move(30,71);
  printw("%5.1f",(float)tempSensor[41]/100.);
  move(32,0);
  printw("--------------------------------------------------------------------------------");
  move(34,2);
  printw("Motor temperatures (C): az1: %2d az2: %2d el1: %2d el2: %2d el3: %2d el4: %2d",
          azm1t,azm2t,elm1t,elm2t,elm3t,elm4t);

  refresh();
}
