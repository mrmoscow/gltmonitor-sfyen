
## CCD Manual and command


### [View PDF Document (F version) ](../ref/SI_Image_SGL_RevF_User_Manual_2523.pdf)

###  📘  Command List and Note

| Function Code | Operation | function | Done? | command package | return packate |  |
| --- | --- | --- | --- | --- | --- | --- |
| 1011 | Get Camera Status | Y |  | struct.pack(">IBBHH", 10, 128, 1, 1011,0) | , |  |
| 1012 | Image Acquisition | Y |  | s.p(">IBBHH+IHHH+lenS", 20+len, 128, 1, 1012,14+len, exptime,Mode,Buffer, as,f) | , |  |
| 1013 | Dark Acquisition | Y |  | s.p(">IBBHH+IHHH+lenS", 20+len, 128, 1, 1013,14+len, exptime,Mode,Buffer, as,f) |  |  |
| 1014 | Test Pattern Acquisition |  |  |  |  |  |
| 1016 | Triggered Acquisition | Y |  |  |  |  |
| 1017 | Inquire Acquisition Status | Y |  |  |  |  |
| 1018 | Terminate Acquisition | Y |  |  |  |  |
| 1019 | Retrieve Image | Y |  |  |  |  |
| 1024 | Get Image Header | Y |  |  |  |  |
| 1028 | Average Light Images Acquisition |  |  |  |  |  |
| 1029 | Average Dark Images Acquisition |  |  |  |  |  |
| 1030 | Average Triggered Images Acquisition |  |  |  |  |  |
| 1031 | Save Image | Y |  |  |  |  |
| 1032 | TDI Acquisition, Internally Paced |  |  |  |  |  |
| 1033 | TDI Acquisition, Externally Paced |  |  |  |  |  |
| 1034 | Set Acquisition Mode | Y |  |  |  |  |
| 1035 | Set Exposure Time | Y |  | struct.pack(">IBBHHI", 14, 128, 1, 1035,4,exptime) |  |  |
| 1036 | Set Acquisition Type | Y |  |  |  |  |
| 1037 | Acquire | Y |  |  |  |  |
| 1038 | Set Number of Averages |  |  |  |  |  |
| 1039 | Set Number of Frames |  |  |  |  |  |
| 1040 | Set Multiple Frame Buffer Mode |  |  |  |  |  |
| 1041 | Get SI Image Settings | Y |  | struct.pack(">IBBHH", 10, 128, 1, 1041, 0) |  |  |
| 1042 | Set Readout Mode | Y |  |  |  |  |
| 1043 | Set CCD Format Parameters |  |  |  |  |  |
| 1044 | Set Single Readout & Format Parameter |  |  |  |  |  |
| 1045 | Set Single Configuration Parameter |  |  |  |  |  |
| 1046 | Cooler On/Off | Y |  |  |  |  |
| 1047 | Set Save to Folder Path |  |  |  |  |  |
| 1048 | Get Camera Parameters | Y |  |  |  |  |
| 1049 | Expose & Shift N Lines |  |  |  |  |  |



## ✳️ Abbreviations & Parameters Explanation
- **Mode:** data  mode: default in this project is 4
  - `1`: transmit to client
  - `2`: hold in buffer.
  - `3`: Save file and transmit to client
  - `4`: Save file and hold in buffer.
- **f:** filenname of saving (end with null,b"\x00")
- **len:** lengh of f(filename)
- **Buffer**: buffer 1 or 2,  default in this project is 2.
- **as:** Save file type as:  default in this project is 0
  - `0`: Fits U16
  - `1`: Fits I16
  - `2`: Fits I32
  - `3`: Fits SGL
  - `4`: TIFF U16
  - `5`: TIFF I16
  - `6`: TIFF I32
  - `7`: TIFF SGL
- **aType(Acquistion Types):**  default is 0
  - `0`: Light
  - `1`: Dark
  - `2`: Test
  - `3`: Triggered
  - `4`: TDI Internally Paced
  - `5`: TDI Externally Paced 
- **RMnum(Readout Mode numbere):** still under definiet. (0~9)



