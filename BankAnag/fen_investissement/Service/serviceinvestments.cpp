#include "serviceinvestments.h"

ServiceInvestments::ServiceInvestments(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    this->setLayout(grid);

    DDateEdit *dateInvestment = new DDateEdit("Date de l'investissement");
    grid->addWidget(dateInvestment,0,0);

    //Groupe de l'info sur l'emprunteur-----------------------
    DGroupBox *groupEmprunteur = new DGroupBox("Information sur l'emprunteur");
    groupEmprunteur->setHeaderBgColor("#00FF7F");
    grid->addWidget(groupEmprunteur,1,0,1,2);

    QGridLayout *gridEmprunteur = new QGridLayout;
    groupEmprunteur->setBodyLayout(gridEmprunteur);

    DLineEdit *invester_fname = new DLineEdit("Nom:");
    gridEmprunteur->addWidget(invester_fname,0,0);

    DLineEdit *invester_lname = new DLineEdit("Prénom:");
    gridEmprunteur->addWidget(invester_lname,0,1);

    DComboBox *invester_sexe = new DComboBox("Sexe:");
    invester_sexe->addItem("M");
    invester_sexe->addItem("F");
    gridEmprunteur->addWidget(invester_sexe,1,0);

    DLineEdit *invester_adresse = new DLineEdit("Adresse:");
    gridEmprunteur->addWidget(invester_adresse,1,1);

    DLineEdit *invester_tel = new DLineEdit("Telephone:");
    gridEmprunteur->addWidget(invester_tel,2,0);



    //Groupe de l'info sur l'investissement
    DGroupBox *groupInvestment = new DGroupBox("Information sur l'investissement");
    groupInvestment->setHeaderBgColor("#00CD66");
    grid->addWidget(groupInvestment,3,0,1,2);

    QGridLayout *gridInvestment = new QGridLayout;
    groupInvestment->setBodyLayout(gridInvestment);

    DComboBox *periodVersement = new DComboBox("Période des versements");
    periodVersement->addItem("Par jour");
    periodVersement->addItem("Par Mois");
    periodVersement->addItem("Par trimestre");
    periodVersement->addItem("Par semestre");
    periodVersement->addItem("Par année");
    gridInvestment->addWidget(periodVersement,0,0);
}
