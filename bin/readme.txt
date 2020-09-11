This C-version of the JPL Ephemeris Export Package was originally written by
Kourosh Arfa-Kaboodvand and was distributed via JPL's ephemeris FTP site, but
not supported by JPL.

Legacy software used by EOST and EOS Space Systems uses the binary output
from this software when built such that sizeof(int) = 4. This version has been
modified to build with gcc on a 64-bit version of Linux.

Aaron Evers

*******************************************************************************
*          Kourosh Arfa-Kaboodvand (Aero-Space Engineer)                      *
*          Technical University of Darmstadt                                  *
*          Institute for Physical and Astronomical Geodesy                    *
*          Petersenstr. 13                                                    *
*          64287 Darmstadt                                                    *
*          Germany                                                            *
*                                                                             *
*          Email: kourosh@ipgs.ipg.verm.tu-darmstadt.de
*******************************************************************************


INSTRODUCTION:
JPL-Planetary and Lunar Ephemeris.

1) Create Binary file from an Ascii file (i.e. ascp2000.200 etc.):

   Remarks: Before starting the asc2eph.exe one have to change all the
            Double precision extensions D via an Editor program to E, e.g.:

                 sed -i s/D/E/g ascp2000.200

  a) Insert the name of the Ascii file (which should be written in Binary
     format) at the end of the corresponding Header file. Actually the Header
     file includes all the relevant names and values for the constants of the
     reference set of data. Besides it includes the computational indizes.
     For more infos see the file header.200 which contains all the importants
     values for the DE-LE200 set of ephemeris. remarks: the values in the
     header file are a function of the relevant set of the ephemeris.
  b) Start the program ASC2EPH.
  c) Enter the name of the header file (i.e. header.200).
  d) Enter the value of the start epoch ( Should be within the time span of
     ascii file. see header file).
  e) Enter the value of the end epoch ( Should be within the time span of
     ascii file. see header file).
  f) Enter the name of the output Binary file.


*******************************************************************************
The included example binary output files were generated on a 64-bit Linux as
follows:

sed -i s/D/E/g ascp2000.200

sed -i s/ascp[0-9]*[.]200/ascp2000.200/ header.200

./asc2eph <<EOF
header.200
2451536.5
2458864.5
bin2000.200
EOF


sed -i s/D/E/g ascp2020.200

sed -i s/ascp[0-9]*[.]200/ascp2020.200/ header.200

./asc2eph <<EOF
header.200
2458832.5
2466160.5
bin2020.200
EOF
