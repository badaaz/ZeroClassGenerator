#include "FenReglage.h"
#include "FenGeneration.h"

FenReglage::FenReglage():QWidget()
{
    setWindowIcon(QIcon("Ruby.png"));
    setWindowTitle("Zero Class Generator");

    m_entetes= new QStringList; //pointeur sur tableau d'entetes
    *m_entetes <<"Nom"<<"Parent"<<"Auteur"<<"Date de création"<<"Rôle de la classe";

    QGroupBox *gbDefinition = new QGroupBox("Définition de la classe");
    m_nom = new QLineEdit;
    m_nomMere = new QLineEdit;
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(m_entetes->at(0),m_nom);
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
    m_auteur= new QLineEdit(this);
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

    connect(btnGenerer, SIGNAL(clicked()), this, SLOT(genererFichier()));
    connect(btnQuitter, SIGNAL(clicked()), this, SLOT(close()));
}


    void FenReglage::genererFichier()
    {
        if (m_nom->text().isEmpty())
        {
            QMessageBox::critical(this,"Erreur","Saisissez le nom de la classe");
            return; //arrêt de la méthode
        }

        QString *streamOut= new QString;


        if (m_gbCommentaires->isChecked())
        {
            streamOut->append("/*\n");
            if (!m_auteur->text().isEmpty()) //verif auteur
            {streamOut->append(m_entetes->at(2)+": "+m_auteur->text()+"\n");}
            streamOut->append(m_entetes->at(3)+ ": "+m_date->text()+"\n");
            if (!m_description->toPlainText().isEmpty()) //verif description
            {streamOut->append(m_entetes->at(4)+": "+m_description->toPlainText()+"\n");} //si description remplie
            streamOut->append("/*\n\n");
        }


        streamOut->append("#ifndef "+(m_nom->text()).toUpper()+"_H\n#define "+(m_nom->text()).toUpper()+"_H");
        streamOut->append("\n\nclass "+m_nom->text());
        if (!m_nomMere->text().isEmpty())
        {streamOut->append(":public "+m_nomMere->text());}
        streamOut->append("\n{");
        if (m_slotsPerso->isChecked())
                {streamOut->append("\n    Q_OBJECT\n\n    public slots:\n");} //si slots personnalisés
        streamOut->append("\n    public:\n");
        if (m_constructeur->isChecked())
                {streamOut->append("    "+m_nom->text()+"();\n");}//si constructeur par defaut
        if (m_destructeur->isChecked())
                {streamOut->append("    ~"+m_nom->text()+"();\n");}//si destructeur
        if (m_accesFilles->isChecked())
                {streamOut->append("\n    protected:\n");} //si acces aux classes enfants
        streamOut->append("\n    private:\n\n};\n#endif");


        FenGeneration *generation = new FenGeneration(*streamOut);   //ATTENTION il faut passer le contenu du pointeur en argument(*)
        generation->exec();


    }


