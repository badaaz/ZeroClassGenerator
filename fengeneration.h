#ifndef FENGENERATION_H
#define FENGENERATION_H

#include <QApplication>
#include <QDialog>
#include <QPlainTextEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QLabel>
#include <QFile>
#include <QTextStream>


class FenGeneration : public QDialog
{
    Q_OBJECT

    public:
    FenGeneration(QString h,QString cpp);
    void creationOnglet(QPlainTextEdit *widget, QString contenu, QString nom);

    public slots:
    void saveFiles();

    private:
    QPlainTextEdit *m_textH;
    QPlainTextEdit *m_textCpp;
    QFontMetrics *m_fm;
    QFont *m_font;
    QTabWidget *m_onglets;

};

#endif // FENGENERATION_H
