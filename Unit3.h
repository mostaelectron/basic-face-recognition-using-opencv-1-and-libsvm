//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#ifndef Unit3H
#define Unit3H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "OpenCV/cv.h"
#include "OpenCV/highgui.h"
#include "SVM/svm.h"
struct svm_node *x;
int max_nr_attr = 64;
struct svm_model* model2;
int predict_probability=0;
String line2 ="";
static int max_line_len2;
static int resultat;
static int resultat_classe;

//-----------------------------------------------------------------------------
String Img_to_vect(IplImage*img)
{
String vect_str;
CvScalar scal;
double val=0;
vect_str="1 ";
int ind =1;
DecimalSeparator ='.';
 for(int i=0;i<img->width;i++)
 {
  for(int j=0;j<img->height;j++)
   {
   scal=cvGet2D(img,j,i);
   val=scal.val[0]/256.0;
    if(val!=0)
     {
      vect_str=vect_str+IntToStr(ind)+":"+FloatToStrF(val,ffGeneral,4,0)+" ";
      ind++;
     }
   }
 }
return vect_str;
}
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------
int get_classe(){return resultat_classe;}
//float get_prob_estimates(){return *prob_estimates;}

void predict_face(char*Model,IplImage*src)
{
double *prob_estimates=NULL;

model2=svm_load_model(Model);
x = (struct svm_node *) malloc((max_nr_attr)*sizeof(struct svm_node));
int correct = 0;
int total = 0;
double error = 0;
double sump = 0, sumt = 0, sumpp = 0, sumtt = 0, sumpt = 0;
int svm_type=svm_get_svm_type(model2);
int nr_class=svm_get_nr_class(model2);

int j;
line2="";
//---------------------------------------------------------------------

     int i = 0;

     double target_label, predict_label;
     char *idx, *val, *label, *endptr;
     int inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
     line2=Img_to_vect(src);//.c_str()"1  1:0 2:0 3:0 4:0 5:0.1 6:0.1275 7:0.0225 8:0 9:0 10:0 11:0 12:0 13:0 14:0 15:0 16:0 17:0 18:0 19:0 20:0 21:0.0925 22:0.135 23:0.0225 24:0 25:0 26:0 27:0 28:0 29:0 30:0 31:0 32:0 33:0 34:0 35:0 36:0 37:0 38:0.055 39:0.1425 40:0.0525 41:0 42:0 43:0 44:0 45:0 46:0 47:0 48:0";
     label = strtok(line2.c_str()," \t");
     target_label = strtod(label,&endptr);
	      while(1)
		{
			if(i>=max_nr_attr-1)	// need one more for index = -1
			{
			      	max_nr_attr *= 2;
			      	x = (struct svm_node *) realloc(x,max_nr_attr*sizeof(struct svm_node));
			}

			idx = strtok(NULL,":");
			val = strtok(NULL," \t");

			if(val == NULL)
				break;
			errno = 0;
			x[i].index = (int) strtol(idx,&endptr,10);
		       	inst_max_index = x[i].index;
                        errno = 0;
		       	x[i].value = strtod(val,&endptr);
		       	++i;
		}
		x[i].index = -1;

		if (predict_probability && (svm_type==C_SVC || svm_type==NU_SVC))
		{
			predict_label = svm_predict_probability(model2,x,prob_estimates);


		}
		else
		{
		 predict_label = svm_predict(model2,x);
                 resultat_classe=int(predict_label);
                }

                 if(predict_label == target_label)
		 ++correct;
		 error += (predict_label-target_label)*(predict_label-target_label);
		 sump += predict_label;
		 sumt += target_label;
		 sumpp += predict_label*predict_label;
		 sumtt += target_label*target_label;
		 sumpt += predict_label*target_label;
		 ++total;

	         if(predict_probability)
		   free(prob_estimates);
svm_destroy_model(model2);
free(x);
}

#endif
