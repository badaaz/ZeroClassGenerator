#include "FenGeneration.h"
#include "FenReglage.h"

FenGeneration::FenGeneration(QString h, QString cpp): QDialog()
{
    setWindowIcon(QIcon("Ruby.png"));
    setWindowTitle("Génération des fichiers");
    m_font= new QFont("Courier",8);
    m_fm= new QFontMetrics(*m_font);
    m_onglets= new QTabWidget;

    QPushButton *btn0= new QPushButton("Enregistrer");
    QPushButton *btn1= new QPushButton("Quitter");

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(btn0);
    layout1->addWidget(btn1);
    layout1->setAlignment(Qt::AlignRight);

    QVBoxLayout *layout0=new QVBoxLayout;
    layout0->addWidget(m_onglets);
    layout0->addLayout(layout1);
    setLayout(layout0);

    creationOnglet(m_textH,h,".h");
    creationOnglet(m_textCpp,cpp,".cpp");

    connect(btn0, SIGNAL(clicked()), this, SLOT(saveFiles()));
    connect(btn1, SIGNAL(clicked()), this, SLOT(close()));
}

    void FenGeneration::creationOnglet(QTextEdit *a, QString b, QString c)
    {
     a= new QTextEdit;
     a->setPlainText(b);
     a->setFont(*m_font);
     a->setReadOnly(true);

     QSize *taille=new QSize(m_fm->size(0,a->toPlainText()));

     int *largeur=new int(taille->width()+15);
     int *hauteur=new int(taille->height()+15);

     if(*largeur>600)
     {a->setMinimumWidth(600);}
     else {a->setMinimumWidth(*largeur);}
     if(*hauteur>800)
     {a->setMinimumHeight(800);}
     else {a->setMinimumHeight(*hauteur);}
     a->setMaximumSize(600,800);

     QVBoxLayout *layout0= new QVBoxLayout;
     layout0->addWidget(a);
     layout0->setSizeConstraint(QLayout::SetMinAndMaxSize);

     QLabel *page=new QLabel;
     page->setLayout(layout0);
     m_onglets->addTab(page,c);
     }

    void FenGeneration::saveFiles()
    {
        QFile *fileH=new QFile(".h");
        if (!fileH->open(QIODevice::WriteOnly | QIODevice::Text))
        {return;}

        QTextStream *streamH=new QTextStream(fileH);
        *streamH<<(m_textH->toPlainText());
    }
