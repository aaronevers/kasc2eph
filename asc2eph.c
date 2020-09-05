/*§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
§                                                                          §
§  ASC2EPH creates a binary JPL Planetary Ephemeris file from a specially  §
§  formatted text file(s).                                                 §
§  For further information, contact:                                       §
§                                                                          §
§                      K. Arfa-Kaboodvand                                  §
§                      Technical University of Darmstadt                   §
§                      Petersenstr.13                                      §
§                      64287 Germany                                       §
§                                                                          §
§                      phone:  49-6151-163809                              §
§                      fax  :  49-6151-164512                              §
§                      email:  KOUROSH@IPGS.VERM.TH-DARMSTADT.DE           §
§                                                                          §
§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


/*========================================================================+
|                                 VOID NRERRO                             |
+=========================================================================+
| AUTOR: K. ARFA-KABOODVAND (Aero-Space Engineer)                         |
+-------------------------------------------------------------------------+
| DESCRIPTION:                                                            |
| Print out the error string.                                             |
+-------------------------------------------------------------------------+
| INPUTS : error_text = String for the error text                         |
+-------------------------------------------------------------------------+
| OUTPUTS:                                                                |
+-------------------------------------------------------------------------+
| REFERENCE: %                                                            |
+========================================================================*/
void nrerror(int WERT,char error_text[])
{
		fprintf(stderr,"\n\n...Run-time error...");
		fprintf(stderr,"\n%d %s",WERT,error_text);
		fprintf(stderr,"\n...now exiting to system...");
		exit(1);
}

/*========================================================================+
|                                 DVECTOR                                 |
+=========================================================================+
| AUTOR: K. ARFA-KABOODVAND (Aero-Space Engineer)                         |
+-------------------------------------------------------------------------+
| DESCRIPTION:                                                            |
| Allocate a double vector with subscript range v[nl..nh].                |
+-------------------------------------------------------------------------+
| INPUTS : nl = Start dimension (subscript range) of the vector           |
|          nh = End dimension (subscript range) of the vector             |
+-------------------------------------------------------------------------+
| OUTPUTS: dvector = Allocated vector                                     |
+-------------------------------------------------------------------------+
| REFERENCE: NUMERICAL RECEPIES IN C                                      |
+========================================================================*/
double *dvector(int nl,int nh)
{
	double *v;

	v=(double *)malloc((size_t) ((nh-nl+1+1)*sizeof(double)));
	if (!v)
		nrerror(0,"allocation failure in dvector()");
	return v-nl+1;
}

/*========================================================================+
|                          FREE_DVECTOR(DOUBLE)                           |
+=========================================================================+
| AUTOR: K. ARFA-KABOODVAND (Aero-Space Engineer)                         |
+-------------------------------------------------------------------------+
| DESCRIPTION:                                                            |
| Free a double vector allocated with dvector().                          |
+-------------------------------------------------------------------------+
| INPUTS : v  = the vector, which should be free.                         |
|          nl = The starting number of row.                               |
+-------------------------------------------------------------------------+
| OUTPUTS: %                                                              |
+-------------------------------------------------------------------------+
| REFERENCE: NUMERICAL RECEPIES IN C                                      |
+========================================================================*/
void free_dvector(double *v,int nl)
{
		free((char *) (v+nl-1));
}

/*========================================================================+
|                              DOUBLE DMATRIX                             |
+=========================================================================+
| AUTOR: K. ARFA-KABOODVAND (Aero-Space Engineer)                         |
+-------------------------------------------------------------------------+
| DESCRIPTION:                                                            |
| Allocate a double matrix with subscript range m[nrl..nrh][ncl..nch].    |
+-------------------------------------------------------------------------+
| INPUTS : nrl = Starting row number (subscript range) of the matrix      |
|          nrh = Ending row number (subscript range) of the matrix        |
|          ncl = Starting column number (subscript range) of the matrix   |
|          nch = Ending column number (subscript range) of the matrix     |
+-------------------------------------------------------------------------+
| OUTPUTS: dmatrix = Allocated matrix                                     |
+-------------------------------------------------------------------------+
| REFERENCE: NUMERICAL RECEPIES IN C                                      |
+========================================================================*/
char **Cmatrix(int nrl, int nrh, int ncl, int nch)
{
	int i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	char **m;

	/* Allocate pointers to rows: */
	m=(char **) malloc((size_t)((nrow+1)*sizeof(char*)));
	if (!m)
				nrerror(0,"allocation failure 1 in matrix()");
	m += 1;
	m -= nrl;

	/* Allocate rows and set pointers to them: */
	m[nrl]=(char *) malloc((size_t)((nrow*ncol+1)*sizeof(char)));
	if(!m[nrl])
			nrerror(0,"allocation failure 2 in matrix()");
	m[nrl] += 1;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++)
					m[i]=m[i-1]+ncol;

	/* Return pointer to array of pointers to rows : */
	return m;
}

/*========================================================================+
|                             FREE_MATRIX(DOUBLE)                         |
+=========================================================================+
| AUTOR: K. ARFA-KABOODVAND (Aero-Space Engineer)                         |
+-------------------------------------------------------------------------+
| DESCRIPTION:                                                            |
| Free a double matrix allocated with dmatrix().                          |
+-------------------------------------------------------------------------+
| INPUTS : m  = the matrix, which should be free.                         |
|          nrl= The starting number of row.                               |
|          ncl= The starting number of column.                            |
+-------------------------------------------------------------------------+
| OUTPUTS: %                                                              |
+-------------------------------------------------------------------------+
| REFERENCE: NUMERICAL RECEPIES IN C                                      |
+========================================================================*/
void free_Cmatrix(double **m, int nrl, int ncl)
/* Free a double matrix allocated by dmatrix() : */
{
		free((char*) (m[nrl]+ncl-1));
		free((char*) (m+nrl-1));
}


/*§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
§§§§§§§§§§§§§§§§§§§§§§§§§  MAIN PROGRAM §§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§
§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§*/
int main(void)
{
/* DECLARATION: */
	int    KSIZE,I,N,J,NCON,IPT[4][13],LPT[4],NROUT,NUMDE,H1,H2,LAUF;
	int    FIRST = TRUE;
	double T1,T2,SS[4],HILFE,*CVAL,AU,DB2Z,EMRAT;
	char   **CNAM,*buf1="AU      ",*buf2="EMRAT   ",*buf3="DENUM   ";
	char   *NAME1 = "            ";
	char   *NAME  = "            ";
	char   *NAME2 = "            ";
	FILE   *fp0,*fp1,*fp2;
	struct{ int NRW,NCOEFF; double *DB;} s;

/* READ THE INITIAL VALUES :*/
	printf("\n1) Name of the header file    = ");scanf("%s",NAME);
	printf("2) Start of the julian date   = ");scanf("%lf",&T1);
	printf("3) End of the julian date     = ");scanf("%lf",&T2);
	printf("4) Name of binary output file = ");scanf("%s",NAME2);

/* READ THE SIZE AND NUMBER OF MAIN EPHEMERIS: */
	if((fp0 = fopen(NAME,"r")) == NULL)
			{ printf(stderr, "Cannot open %s file.\n",NAME);
					return 1;
			};
	fscanf(fp0,"%d",&KSIZE);

/* READ START AND END AND SPAN TIME (GROUP 1030): */
	for(I = 1;I <= 3; ++I)
				fscanf(fp0,"%lf",&SS[I]);

	if(T1< SS[1] || T2>SS[2])
			{ printf(stderr, "The given time span is not within the allowable time!");
					return 1;
			};

/* READ THE NUMBER AND NAMES OF CONSTANTS: (GROUP 1040/4):*/
	fscanf(fp0,"%d",&NCON);
	CNAM = Cmatrix(1,NCON,0,8);
	for(I = 1;I <= NCON; ++I)
				{ fscanf (fp0,"%s",CNAM[I]);
						H1=8-strlen(CNAM[I]);
						if(H1==1)CNAM[I]=strcat(CNAM[I]," ");
						if(H1==2)CNAM[I]=strcat(CNAM[I],"  ");
						if(H1==3)CNAM[I]=strcat(CNAM[I],"   ");
						if(H1==4)CNAM[I]=strcat(CNAM[I],"    ");
						if(H1==5)CNAM[I]=strcat(CNAM[I],"     ");
						if(H1==6)CNAM[I]=strcat(CNAM[I],"      ");
						if(H1==7)CNAM[I]=strcat(CNAM[I],"       ");
				}

/* READ NUMBER OF VALUES AND VALUES (GROUP 1041/4): */
	fscanf(fp0,"%d",&N);
	CVAL = dvector(1,NCON);
	for(I = 1;I <= NCON; ++I)
				{ fscanf(fp0,"%lf",&HILFE);
						CVAL[I] = HILFE;
				}

	for(I = 1;I <= NCON; ++I)
				{
					if((strcmp(CNAM[I],buf1))==0)
								AU=CVAL[I];
					if((strcmp(CNAM[I],buf2))==0)
								EMRAT=CVAL[I];
					if((strcmp(CNAM[I],buf3))==0)
								NUMDE=(int)(CVAL[I]);
				}

/* READ POINTERS NEEDED BY INTERP (GROUP 1050): */
	for(I = 1;I <= 3; ++I)
				{ for(J = 1;J <= 12; ++J)
									{ fscanf(fp0,"%d",&H1);
											IPT[I][J]=H1;
									}
						fscanf(fp0,"%d",&H2);
						LPT[I] = H2;
				}

/* READ THE NAME OF EPHEMERIS DATA (GROUP 1070) & CLOSE HEADER FILE: */
	fscanf(fp0,"%12s",NAME1);
	fclose(fp0);

/* OPEN THE EPHEMERIS FILE (NAME1):*/
/* OPEN THE EPHEMERIS FILE FOR CHECKING THE DIMENSION AND TIME CHECKING */
/* (NAME1):                                                             */
	if((fp2 = fopen(NAME1,"r")) == NULL)
			{ printf(stderr, "Cannot open %s file.\n",NAME1);
					return 1;
			};

/* READ THE BLOCK NR NUMBER OF COEFFICIENTS AND THE COEFFICIENT: */
	NROUT  = 0;
	fscanf(fp2,"%d",&(s.NRW));   /* Read the block number!           */
	fscanf(fp2,"%d",&(s.NCOEFF));/* Read the number of coefficients! */
	/* CHECK IF THE NUMBER OF COEFFICIENTS CORESPONDS TO THE NR. OF  */
	/* COLUMNS OR NOT FOR EXAMPLE IN CASE OF ASC+1980.200 THE NR. OF */
	/* COEFFICIENTS IS EQUAL TO 826 BUT THE NUMBER OF DATA IS EQUAL  */
	/* TO 276*3=828 :                                                */
	LAUF = s.NCOEFF;
	for(;;)
				{ if((LAUF%3) != 0)
								LAUF+=1;
						else
								break;
				}
	s.DB = dvector(1,LAUF);      /* Initialise the vector DB!        */

	/* READ THE COEFFICIENTS: */
	for(I = 1; I <= LAUF; ++I)
				{ fscanf(fp2,"%lf",&HILFE);
						s.DB[I] = HILFE;
				}

/* OPEN BINARY OUTPUT FILE (NAME2): */
	if((fp1 = fopen(NAME2, "wb")) == NULL)
			{ fprintf(stderr, "Cannot open %s file.\n",NAME2);
					return 1;
			};

/* >>>>>>>>> COMPUTATION LOOP: <<<<<<<<<<<<<*/
	printf("\nWRITE THE EPHEMERIS IN THE FILE:\n");
	DB2Z=0.;

	for(;;)
				{
						if(feof(fp2))break;

						if(s.DB[1]>=T1 && s.DB[2]<=T2)
								{
									/* Skip this data block if the end of the interval is less     */
									/* than the specified start time or if it does not begin there */
									/* where the previous block ended.                             */
									if((s.DB[2]>=T1) && (s.DB[1]>=DB2Z) )
											{ if(FIRST)
															{ /* Don't worry about the intervals overlapping or     */
																	/* abutting if this is the first applicable interval. */
																	DB2Z  = s.DB[1];
																	FIRST = FALSE;
															}
													if((s.DB[1])!= DB2Z )
															{ /* Beginning of current interval is past the end  */
																	/* of the previous one.                           */
																	nrerror(s.NRW,"Records do not overlap or abut");
															}
													DB2Z  = s.DB[2];
													/* Update the user as to our progress every 10th block.*/
													if((NROUT%10) == 0)
															{ if(s.DB[1] >= T1)
																			printf("\n   Ephemeris nr: %6d  Last JED = %24.14g",s.NRW,
																										s.DB[2]);
																	else
																			printf("\n Searching for first requested record...");
															}
													NROUT += 1;
													for(I=1;I<=s.NCOEFF;++I)
																				fwrite(&s.DB[I],sizeof(double),1, fp1);

													/* Save this block's starting date, its interval span, and */
													/* its end date.                                           */
													if(NROUT==1)
															{ SS[1] = s.DB[1];
																	SS[3] = s.DB[2] - s.DB[1];
															}
													SS[2] = s.DB[2];
											}
								}
						if(s.DB[2]==T2)break;
						fscanf(fp2,"%d",&(s.NRW));
						if(feof(fp2))break;
						fscanf(fp2,"%d",&(s.NCOEFF));
						for(I = 1;I <= LAUF; ++I)
									{ fscanf(fp2,"%lf",&HILFE);
											s.DB[I] = HILFE;
									}
						if(s.DB[1]>=T2)break;
				} /* END OF COMPUTATION LOOP ! */

		printf("\n\n   Ephemeris nr: %6d  Last JED = %24.14g",s.NRW,s.DB[2]);

		/* WRITE OUTPUT TO THE OUTPUT BINARY FILE (VARIABLES;CONSTANTS; ETC.): */
		fwrite(&KSIZE,sizeof(int), 1, fp1);
		for(I = 1;I <= NCON; ++I)
				fwrite(CNAM[I],strlen(CNAM[I])+1,1, fp1);

		for(I = 1;I <= NCON; ++I)
				fwrite(&(CVAL)[I],sizeof(double), 1, fp1);
		for(I = 1;I <= 3; ++I)
				fwrite(&SS[I],sizeof(double), 1, fp1);
		fwrite(&AU,sizeof(double), 1, fp1);
		fwrite(&EMRAT,sizeof(double), 1, fp1);
		fwrite(&NUMDE,sizeof(int), 1, fp1);
		for(J = 1;J <= 3; ++J)
				for(I=1;I<=12;++I)
							fwrite(&IPT[J][I],sizeof(int), 1, fp1);
		for(I = 1;I <= 3; ++I)
					fwrite(&LPT[I],sizeof(int), 1, fp1);
		fwrite(&NCON,sizeof(int), 1, fp1);

		fclose(fp1);
		fclose(fp0);
		free_Cmatrix(CNAM,1,0);
		printf("\n\n END OF PROGRAMM !\n\n");

		return 0;
}
