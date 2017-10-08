#ifndef FENGENERATION_H
#define FENGENERATION_H

#include <QApplication>
#include <QDialog>
#include <QTextEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>


class FenGeneration : public QDialog
{
    public:
    FenGeneration(QString streamOut); // CORRECTION

    private:
    QTextEdit *m_streamIn;

};

#endif // FENGENERATION_H
