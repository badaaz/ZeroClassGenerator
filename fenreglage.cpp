#include "FenReglage.h"
#include "FenGeneration.h"

FenReglage::FenReglage():QWidget()
{
    setWindowIcon(QIcon("Ruby.png"));
    setWindowTitle("Zero Class Generator");

    m_entetes= new QStringList; //pointeur sur tableau d'entetes
    *m_entetes <<"Nom"<<"Parent"<<"Auteur"<<"Date de création"<<"Rôle de la classe"<<"Header"; // de 0 à 5

    QGroupBox *gbDefinition = new QGroupBox("Définition de la classe");
    m_nom = new QLineEdit;
    m_nom->setMaxLength(20);
    m_nom->setInputMask(">x<xxxxxxxxxxxxxxxxxxx");
    m_nomHeader= new QLineEdit;
    m_nomHeader->setMaxLength(22);
    m_nomHeader->setInputMask(">xxxxxxxxxxxxxxxxxxxx[xx]");
    m_nomMere = new QLineEdit;
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(m_entetes->at(0),m_nom);
    layout1->addRow(m_entetes->at(5),m_nomHeader);
    layout1->addRow(m_entetes->at(1),m_nomMere);
    gbDefinition->setLayout(layout1);


    QGroupBox *gbOptions = new QGroupBox("Options");
    m_constructeur= new QCheckBox("Inclure le &Constructeur par défaut");
    m_destructeur= new QCheckBox("Inclure le &Destructeur");
    m_accesFilles= new QCheckBox("Permettre l'&accès aux classes filles");
    m_slotsPerso= new QCheckBox("&Slot(s) personnalisé(s)");


    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(m_constructeur);
    layout2->addWidget(m_destructeur);
    layout2->addWidget(m_slotsPerso);
    layout2->addWidget(m_accesFilles);
    gbOptions->setLayout(layout2);
    m_gbCommentaires= new QGroupBox("Commentaires");
    m_gbCommentaires->setCheckable(true);
    m_gbCommentaires->setChecked(false);
    m_auteur= new QLineEdit;
    m_date= new QDateEdit;
    m_date->setMinimumDate(QDate::currentDate());
    m_description= new QTextEdit;

    QFormLayout *layout3 = new QFormLayout;
    layout3->addRow(m_entetes->at(2),m_auteur);
    layout3->addRow(m_entetes->at(3),m_date);
    layout3->addRow(m_entetes->at(4),m_description);
    m_gbCommentaires->setLayout(layout3);

    QPushButton *btnGenerer= new QPushButton("Générer");
    QPushButton *btnQuitter= new QPushButton("Quitter");
    QHBoxLayout *layout4= new QHBoxLayout;
    layout4->addWidget(btnGenerer);
    layout4->addWidget(btnQuitter);
    layout4->setAlignment(Qt::AlignRight);

    QVBoxLayout *layout0 = new QVBoxLayout;
    layout0->addWidget(gbDefinition);
    layout0->addWidget(gbOptions);
    layout0->addWidget(m_gbCommentaires);
    layout0->addLayout(layout4);

    setLayout(layout0);

    connect(btnGenerer, SIGNAL(clicked()), this, SLOT(genererFichiers()));
    connect(btnQuitter, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_nom, SIGNAL(textEdited(QString)),this, SLOT(majHeader(QString)));
    connect(m_nomHeader, SIGNAL(textEdited(QString)),this, SLOT(majNom(QString)));
}


    void FenReglage::genererFichiers()
    {
        if (m_nom->text().isEmpty())
        {
            QMessageBox::critical(this,"Erreur","Saisissez le nom de la classe");
            return; //arrêt de la méthode
        }
        FenGeneration *generation = new FenGeneration(creationH(),creationCpp());   //ATTENTION il faut passer le contenu du pointeur en argument(*)
        generation->exec();
    }

    void FenReglage::majHeader(const QString nomClasse)
    {
        QString *tmp = new QString(nomClasse);
        if (tmp->isEmpty())
        {m_nomHeader->setText("");}
        else {m_nomHeader->setText(*tmp+"_h");}
    }

    void FenReglage::majNom(const QString nomHeader)
    {
        QString *tmp = new QString(nomHeader);
        tmp->remove("_h", Qt::CaseInsensitive);
        if (tmp->isEmpty())
        {m_nom->setText("");}
        else {m_nom->setText(*tmp);}
    }

    QString FenReglage::creationH()
    {
        QString *stream= new QString;
        if (m_gbCommentaires->isChecked())
        {
            stream->append("/*\n");
            if (!m_auteur->text().isEmpty()) //verif auteur
            {stream->append(m_entetes->at(2)+": "+m_auteur->text()+"\n");}
            stream->append(m_entetes->at(3)+ ": "+m_date->text()+"\n");
            if (!m_description->toPlainText().isEmpty()) //verif description
            {stream->append(m_entetes->at(4)+": "+m_description->toPlainText()+"\n");} //si description remplie
            stream->append("/*\n\n");
        }
        stream->append("#ifndef "+(m_nomHeader->text())+"\n#define "+(m_nomHeader->text()));
        stream->append("\n\nclass "+m_nom->text());
        if (!m_nomMere->text().isEmpty())
        {stream->append(":public "+m_nomMere->text());}
        stream->append("\n{");
        if (m_slotsPerso->isChecked())
                {stream->append("\n    Q_OBJECT\n\n    public slots:\n");} //si slots personnalisés
        stream->append("\n    public:\n");
        if (m_constructeur->isChecked())
                {stream->append("    "+m_nom->text()+"();\n");}//si constructeur par defaut
        if (m_destructeur->isChecked())
                {stream->append("    ~"+m_nom->text()+"();\n");}//si destructeur
        if (m_accesFilles->isChecked())
                {stream->append("\n    protected:\n");} //si acces aux classes enfants
        stream->append("\n    private:\n\n};\n#endif");
        return *stream;
    }

    QString FenReglage::creationCpp()
    {
        QString *stream= new QString;
        stream->append("#include \""+ m_nom->text()+".h\"\n"); // "\" pour echapper un caractere
        stream->append("\n");
        if (m_constructeur->isChecked())
        {stream->append(m_nom->text()+"::"+m_nom->text()+"():Q......()\n{\n}\n");}
        if (m_destructeur->isChecked())
        {stream->append(m_nom->text()+"::~"+m_nom->text()+"()\n{\n}\n");}
        stream->append("\n");
        return *stream;
   }

    QString FenReglage::getNom()
    {
       return m_nom->text();
    }
