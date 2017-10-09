#include "FenGeneration.h"

FenGeneration::FenGeneration(QString streamOut): QDialog()
{
    setWindowIcon(QIcon("Ruby.png"));
    setWindowTitle(".h");
    int tailleFont(8);
    QFont police("Courier",tailleFont,QFont::Bold);
    m_streamIn= new QTextEdit;
    m_streamIn->setPlainText(streamOut);
    m_streamIn->setFont(police);
    m_streamIn->setReadOnly(true);



    QFontMetrics fm(police);
    QSize taille=fm.size(0,m_streamIn->toPlainText());

    int largeur=taille.width()+15;
    int hauteur=taille.height()+15;

    if(largeur>600)
    {m_streamIn->setMinimumWidth(600);}
    else {m_streamIn->setMinimumWidth(largeur);}
    if(hauteur>800)
    {m_streamIn->setMinimumHeight(800);}
    else {m_streamIn->setMinimumHeight(hauteur);}
    m_streamIn->setMaximumSize(600,800);


    QPushButton *btn1= new QPushButton("Quitter");
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(btn1);
    layout1->setAlignment(Qt::AlignRight);

    QVBoxLayout *layout0= new QVBoxLayout;
    layout0->addWidget(m_streamIn);
    layout0->addLayout(layout1);
    layout0->setSizeConstraint(QLayout::SetMinAndMaxSize);
    this->setLayout(layout0);


    connect(btn1, SIGNAL(clicked()), this, SLOT(close()));
}
