//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "OpenCv/cv.h"
#include "OpenCv/highgui.h"
#include "SVM/svm.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TSaveDialog *SaveTrain;
        TSaveDialog *SaveModel;
        TGroupBox *GroupBox3;
        TOpenDialog *OpenModel;
        TBitBtn *BitBtn5;
        TBitBtn *BitBtn6;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TComboBox *classes;
        TEdit *edit_label;
        TLabel *Label2;
        TBitBtn *BitBtn7;
        TMemo *Train_Memo;
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall detect_train_face( IplImage* org_img );
        void __fastcall face_detect_recognition( IplImage* img );        
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
