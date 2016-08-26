//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//string array for train
char**name_parametre;
String Model;

char* cascade_name = "haarcascade_frontalface_alt.xml";

CvHaarClassifierCascade* cascade = 0;
static CvMemStorage* storage = 0;
IplImage* src;
IplImage* i_Gray,* i_Gray_resize;
bool  capture_f=false;

CvScalar  b_col = {255,0,0};
CvScalar  r_col = {0,255,0};
CvScalar  g_col = {0,0,255};

CvFont font;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//------------------------Train_image--------------------------------------
String img_to_vect(IplImage*img,int classe)
{
String vect_str;
CvScalar scal;
double val=0;
vect_str=IntToStr(classe)+" ";
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
//---------------------------------------------------------------------------


void __fastcall TForm1:: detect_train_face( IplImage* org_img )
{
    IplImage *frame= 0;
    IplImage *small_f= 0;
    IplImage *small_f_resized= 0;
    IplImage *gray_face= 0;
    IplImage* gray = 0;
    // resize image
    frame = cvCreateImage( cvSize(400 , 400), 8, 3 );
    cvResize(org_img,frame);

    // gray image
    gray = cvCreateImage( cvSize(frame->width, frame->height), 8, 1 );
    cvCvtColor( frame, gray, CV_BGR2GRAY );


    // Egalisation to increase contrast
    cvEqualizeHist(gray, gray);


//    String  haarClassifierCascadePath = GetCurrentDir() + "OpenCv/haarcascade_frontalface_alt2.xml";
 //   cascade_name = haarClassifierCascadePath.c_str();
    cascade_name = "C:\\haarcascade_frontalface_default.xml";
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    // faces sequence storage memory
    storage = cvCreateMemStorage(0);
    cvClearMemStorage( storage );
    //si le ficher l'apprantissage est chrarger
    if( cascade )
     {
        //on lance la détection
        CvSeq* faces = cvHaarDetectObjects( gray, cascade, storage,1.2, 2, 0, cvSize(100, 100) );
        //pour chaque visage trouver
        for( int i = 0; i < (faces ? faces->total : 0); i++ )
         {
          //extraire le rect qui encadre le visage
          CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

          //Draw rect of face
          CvPoint  p1, p2;
          int radius;
          p1.x= (r->x);
          p1.y= (r->y);
          p2.x= p1.x + r->width;
          p2.y= p1.y + r->height;
          cvRectangle(frame, p1 , p2 , g_col);

          //Draw circle face
          CvPoint center;
          center.x = cvRound((r->x + r->width*0.5));
          center.y = cvRound((r->y + r->height*0.5));
          radius = cvRound((r->width + r->height)*0.25);
          cvCircle( frame, center, radius, r_col , 3, 8, 0 );

          //Draw small rect inside circle
          p1.x= (center.x-radius) + ceil(0.3*radius);
          p1.y= (center.y-radius) + ceil(0.3*radius);
          int w_small_r= 2*ceil(0.7*radius);
          int h_small_r= 2*ceil(0.7*radius);
          p2.x= p1.x + w_small_r;
          p2.y= p1.y + h_small_r;
          cvRectangle(frame, p1 , p2 , b_col);

          //image for small rect
          small_f = cvCreateImage(cvSize(w_small_r, h_small_r), 8, 3 );
          //copy small rect image
          CvScalar scal;
          for(int i=p1.x; i<p1.x + w_small_r; i++)
           for(int j=p1.y; j<p1.y + h_small_r; j++)
            {
             scal=cvGet2D(frame,j,i);
             cvSet2D(small_f,j-p1.y,i-p1.x,scal);
             cvSet2D(frame,j-p1.y,i-p1.x,scal);
            }
          //image 30x30 px
          small_f_resized = cvCreateImage(cvSize(30,30), 8, 3 );
          //la convertir en gray dans face_resize_g
          gray_face = cvCreateImage(cvSize(small_f_resized->width,small_f_resized->height), 8, 1 );
          //resize small sect to 30x30 px
          cvResize(small_f,small_f_resized);
          //create face_resize gray 30*30 in face_resize_g
          cvCvtColor(small_f_resized, gray_face, CV_BGR2GRAY );
          //EqualizeHistogramme of face_resize_g
          cvEqualizeHist(gray_face, gray_face);

          //if key space is pressed then add image to train
          if(capture_f)
           {
            Train_Memo->Lines->Add(img_to_vect(gray_face, classes->ItemIndex+1));
            capture_f=false;
           }
          cvShowImage("result", frame);
          cvShowImage("train_face", gray_face);
         }
      }
          cvReleaseImage(&frame);
          cvReleaseImage(&small_f);
          cvReleaseImage(&small_f_resized);
          cvReleaseImage(&gray_face);
          cvReleaseImage(&gray);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::face_detect_recognition( IplImage* img )
{
 IplImage *face=0;
 IplImage *face_resize=0,*face_resize_g=0;

    //Différentes couleurs pour différentes visages détectés
    static CvScalar colors[] =
     {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
     };

    // échele pour enelever les bords de l'image orig
    double scale = 1.3;

    int i;

    // pour convert l'image org en niveau de gris
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );

    // Pour contenir l'image en gray sans les bords
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),8, 1 );

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );

    cvSmooth(small_img,small_img,CV_GAUSSIAN);

    // Egalisation de l'hist pour augmanter le contraste
    cvEqualizeHist( small_img, small_img );


    // espace mémoire pour contenir les sequences des visage
    cvClearMemStorage( storage );

    //si le ficher l'apprantissage est chrarger
    if( cascade )
    {
        //on lance la détection
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade,storage,
                                            1.2, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(80, 80) );
        //pour chaque visage trouver
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            //extraire le rect qui encadre le visage
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            CvPoint p1,p2;
            p1.x= r->x*scale;
            p1.y= r->y*scale;
            p2.x=p1.x + r->width*scale;
            p2.y=p1.y  + r->height*scale;
            cvRectangle(img, p1, p2,colors[i%8]);



            //Draw circle in org img
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            //cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );

            //make small rect inside circle
            CvPoint p, p_;
            p.x=center.x-radius;
            p.y=center.y-radius;
            p_.x=p.x+ceil(0.3*radius);
            p_.y=p.y+ceil(0.3*radius);

            int width_=2*ceil(0.7*radius);
            int height_=2*ceil(0.7*radius);

            //declaration d'une image de la taille du small rect
            face = cvCreateImage(cvSize(width_,height_), 8, 3 );

            //declaration d'une image de la taille 30*30 pour la reconnaissance
            face_resize = cvCreateImage(cvSize(30,30), 8, 3 );
            //la convertir en gray dans face_resize_g
            face_resize_g = cvCreateImage(cvSize(face_resize->width,face_resize->height), 8, 1 );

            //remplir l'image du small rect
            CvScalar scal;
            for(int i=p_.x; i<p_.x+width_; i++)
             for(int j=p_.y; j<p_.y+height_; j++)
              {
               scal=cvGet2D(img,j,i);
               cvSet2D(face,j-p_.y,i-p_.x,scal);
              }

            //resize face to 30*30 in face_resize
            cvResize(face,face_resize);
            //create face_resize gray 30*30 in face_resize_g
            cvCvtColor(face_resize, face_resize_g, CV_BGR2GRAY );
            //EqualizeHistogramme of face_resize_g
            cvEqualizeHist(face_resize_g,face_resize_g);
            //predicte face_resize_g with SVM
            predict_face(Model.c_str(),face_resize_g);
            //Draw label of classe inside circle in org img
            String s= classes->Items->Strings[get_classe()-1];
            cvPutText(img,s.c_str(), center,&font, colors[i%8]);

            //Draw label of classe inside circle in org img
            cvReleaseImage(&face);
            cvReleaseImage(&face_resize);
            cvReleaseImage(&face_resize_g);
        }
    }
    cvShowImage( "result", img );
    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
    CvCapture *capture = 0;
    IplImage *frame = 0;

    capture = cvCaptureFromCAM(0);
    cvNamedWindow( "result", 1 );
    cvNamedWindow( "train_face", 1 );

    if( capture )
     {
       for(;;)
       {
        frame = cvQueryFrame( capture );
        if( !frame )
          break;

        detect_train_face(frame);
        if(cvWaitKey(10)>=0)
          break;
       }
     }
    cvReleaseImage( &frame );
    cvReleaseCapture( &capture );
    cvDestroyWindow("result");
    cvDestroyWindow("train_face");
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
 capture_f=true;
}
//---------------------------------------------------------------------------





void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
 if(Train_Memo->Text!="")
  {
   if(SaveTrain->Execute())
    {
     Train_Memo->Lines->SaveToFile(SaveTrain->FileName);
     name_parametre[5]=SaveTrain->FileName.c_str();
    }
  }
  else
  {
   ShowMessage("Fichier Train vide !!!");
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 //initialisation       
 Train_Memo->Clear();
 if(name_parametre==NULL)
 {
  name_parametre=new char* [sizeof(char*)*7];
  name_parametre[0]=new char [sizeof(char)*100];//fonction
  name_parametre[1]=new char [sizeof(char)*100];//-t
  name_parametre[2]=new char [sizeof(char)*100];//0
  name_parametre[3]=new char [sizeof(char)*100];//-c
  name_parametre[4]=new char [sizeof(char)*100];//100
  name_parametre[5]=new char [sizeof(char)*100];//traion.trn
  name_parametre[6]=new char [sizeof(char)*100]; // model.mdl
 }
// label_classe->Items->LoadFromFile("Nom.txt");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
 if(SaveModel->Execute())
 {

  //foction -t 0 -c 100 trin.trn model.mdl
  //   0     1 2  3  4      5        6
  name_parametre[1]="-t";
  name_parametre[2]="3";
  name_parametre[3]="-c";
  name_parametre[4]="1000000";
  name_parametre[6]=SaveModel->FileName.c_str();
  Train(7,name_parametre);

 }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
 Model="";
 if(OpenModel->Execute())
  Model=OpenModel->FileName.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn6Click(TObject *Sender)
{
    IplImage *frame, *frame_copy = 0;
    CvCapture* capture = 0;


    // cascade_name = "C:\\haarcascade_frontalface_alt2.xml";
    cascade_name = "C:\\haarcascade_frontalface_default.xml";

    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

    storage = cvCreateMemStorage(0);
    capture = cvCaptureFromCAM(0);
    cvNamedWindow( "result", 1 );

    //initialialisation de la font pour un draw dans l'image
    cvInitFont( &font,CV_FONT_HERSHEY_TRIPLEX , 1.0f, 1.0f,0,2,8 );

    if( capture )
     {
      for(;;)
       {
        if( !cvGrabFrame( capture ))
         break;
        frame = cvQueryFrame( capture );
        if( !frame )
         break;
        frame_copy = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_8U, frame->nChannels );
        if( frame->origin == IPL_ORIGIN_TL )
         cvCopy( frame, frame_copy, 0 );
        else
         cvFlip( frame, frame_copy, 0 );

        face_detect_recognition( frame_copy );

        if( cvWaitKey(10) >=0 )
         break;
       }
      cvReleaseImage( &frame_copy );
      cvReleaseCapture( &capture );
     }
    cvDestroyWindow("result");


}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn7Click(TObject *Sender)
{
if(edit_label->Text!="")
{
 classes->Items->Add(edit_label->Text);
 edit_label->Text="";
}
        
}
//---------------------------------------------------------------------------

