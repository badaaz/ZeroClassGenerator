#ifndef FENREGLAGE_H
#define FENREGLAGE_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QString>
#include <QStringList>



class FenReglage:public QWidget
{
    Q_OBJECT        //utilisation de slot perso

    public:
    FenReglage();
    QString creationH();
    QString creationCpp();
    QString getNom(); //accesseur


    public slots:
    void genererFichiers();
    void majHeader(const QString nomClasse);
    void majNom(const QString nomHeader);

    private:
    QLineEdit *m_nom;
    QLineEdit *m_nomHeader;
    QLineEdit *m_nomMere;

    QCheckBox *m_constructeur;
    QCheckBox *m_destructeur;
    QCheckBox *m_accesFilles;
    QCheckBox *m_slotsPerso;

    QLineEdit *m_auteur;
    QDateEdit *m_date;
    QTextEdit *m_description;

    QStringList *m_entetes;
    QGroupBox *m_gbCommentaires;

};

#endif // FENREGLAGE_H
