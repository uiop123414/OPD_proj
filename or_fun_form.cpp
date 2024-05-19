#include "or_fun_form.h"
#include "ui_or_fun_form.h"
#include <formula.h>


#include <QString>
Or_fun_form::Or_fun_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Or_fun_form)
{
    ui->setupUi(this);

    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Form"));


    QObject::connect(ui->OkBtn, SIGNAL(clicked()), this, SLOT(new_accept()));

    QObject::connect(ui->MoveOne, SIGNAL(clicked()), this, SLOT(MoveOne()));
    QObject::connect(ui->DemoveOne, SIGNAL(clicked()), this, SLOT(DeMoveOne()));
    QObject::connect(ui->MoveAll, SIGNAL(clicked()), this, SLOT(MoveAll()));
    QObject::connect(ui->DemoveAll, SIGNAL(clicked()), this, SLOT(DeMoveAll()));

    QObject::connect(ui->ChoosenFormulas, &QListWidget::itemSelectionChanged, this, &Or_fun_form::moveAllToThirdList);




}

void Or_fun_form::quantifierAllFormulas(vector <EntityBase *> * entities, int type)
{
    tstring str;
    // � ����� ���� �������, ������� � �������� ��������� ����������� �������� �� ���� ��������� ���������� ���������
    for (size_t i = 0; i <entities->size(); i++)
    {
        EntityBase * base = entities->at(i);
        if ( !base->isFormula() )
            continue;
        Formula * icurr = (Formula *)base;
        icurr->quantifierFormula(entities, (EntityBaseType) type);
    }
}

void Or_fun_form::negativeAllFormulas(vector <EntityBase *> * entities){
    int k = entities->size();
    for (int i = 0; i < k; i++)
    {
        EntityBase * base = entities->at(i);
        if ( !base->isFormula() )
            continue;
        Formula * icurr = (Formula *)base;
        if (icurr->isNegative())
            continue;
        icurr->negativeFormula(entities);
    }
}

Or_fun_form::~Or_fun_form()
{
    delete ui;
}

void Or_fun_form::moveAllToThirdList() {
    // Clear the third list first to ensure no items are duplicated
    ui->listWidget_3->clear();

    QListWidgetItem *selectedItem = ui->ChoosenFormulas->currentItem();

    if(this->type == 0 or this->type ==  1 or this->type == 2){ // for AND OR NEGATIVE funcs
        // Move all items from ChoosenFormulas and ExistedFormulas to listWidget_3 except the selected item
        int choosenItemCount = ui->ChoosenFormulas->count();
        for(size_t i = 0; i < choosenItemCount; ++i) {
            QListWidgetItem *item = ui->ChoosenFormulas->item(i);
            if (item != selectedItem) {
                ui->listWidget_3->addItem(item->clone());
            }
        }

        int existedItemCount = ui->ExistedFormulas->count();
        for(size_t i = 0; i < existedItemCount; ++i) {
            QListWidgetItem *item = ui->ExistedFormulas->item(i);
            if (item != selectedItem) {
                ui->listWidget_3->addItem(item->clone());
            }
        }
    }
    else{
        std::cout<<"hello"<<std::endl;
        QString selectedText = selectedItem->text();


        EntityBase * item;

        for (EntityBase* entity : all_entities) {

                if (entity->getText() == selectedText) {

                    std::cout<< "f->possibleVariables.size()"<<std::endl;
                    item = entity;
                    break;
                }
        }


        Formula * f = (Formula *)item;
        std::cout<< f->possibleVariables.size()<<std::endl;
        std::cout<< QString::fromStdWString(item->getText()).toStdString().c_str()<<std::endl;


        for (size_t i = 0; i < f->possibleVariables.size(); i++){

            auto res = QString::fromStdWString(f->possibleVariables[i]->GetText()->data()).toStdString().c_str();
            ui->listWidget_3->addItem(QListWidgetItem(res).clone());


        }

    }
}

// Assuming item is a QListWidgetItem pointer
QVariant  Or_fun_form::getItemData(const QListWidgetItem *item) {
    if (item) {
        int index = ui->ChoosenFormulas->row(item);
        return ui->ChoosenFormulas->model()->data(ui->ChoosenFormulas->model()->index(index, 0));
    }
    return QVariant();


}
void Or_fun_form::new_accept()
{
    Formula * formula;
    switch (this->type)

    {
    case QUANTIFIER1_OPERATION:
    case QUANTIFIER2_OPERATION:
        if(ui->CheckToAll1->isChecked())
        {
            if(formulas->size() > 0)
                this->quantifierAllFormulas(&all_entities, this->type);
        }
        else
        {

            QListWidgetItem *selectedItem = ui->ChoosenFormulas->currentItem();
            QString selectedText = selectedItem->text();


            EntityBase * item;

            for (EntityBase* entity : all_entities) {

                    if (entity->getText() == selectedText) {

                        item = entity;
                        break;
                    }
            }


            Formula * f = (Formula *)item;


            QListWidgetItem *selectedItemDown = ui->listWidget_3->currentItem();
            QString selectedItemTextDown = selectedItemDown->text();

            EntityVariable * pev;


            for (EntityVariable* entity :  f->possibleVariables) {

                    if (QString::fromStdWString(entity->GetText()->data()) == selectedItemTextDown) {
                        std::cout<<"Hello 4"<<std::endl;

                        pev = entity;
                        break;
                    }
            }


            std::cout<<"Hello 5"<<std::endl;
            if(pev!=nullptr){

                std::cout<<"Hello 6"<<std::endl;
                formula=f->quantifierFormula(&all_entities, (EntityBaseType) this->type, pev);
            }

            break;

        }

    case 2:
        if(ui->CheckToAll1->isChecked())
        {
            if(formulas->size() > 0)
                negativeAllFormulas(&all_entities);
        }
        else
        {
            if(ui->CheckToAll2->isChecked())
            {

                    Formula * f = new Formula();
                    if(f)
                       f->negativeFormula(&all_entities);


            }
            else
            {
                QListWidgetItem *selectedItem = ui->ChoosenFormulas->currentItem();
                QString selectedText = selectedItem->text();


                EntityBase * item;

                for (EntityBase* entity : all_entities) {

                        if (entity->getText() == selectedText) {

                            item = entity;
                            break;
                        }
                }


                Formula * f = (Formula *)item;
                formula = f->negativeFormula(&all_entities);


            }
        }
        break;

    case 1:
    case 0:

        EntityBaseType operation;

        if(this->type==0)
            operation = AND_OPERATION;
        else if(this->type==1)
            operation = OR_OPERATION;


        if(ui->CheckToAll1->isChecked())
        {
            if(formulas->size() > 0)
                joinAllFormulas(&all_entities, operation);
        }
        else
        {

                QListWidgetItem *selectedItemChosen = ui->ChoosenFormulas->currentItem();
                QString selectedTextChosen = selectedItemChosen->text();


                EntityBase * itemCh;

                for (EntityBase* entity : all_entities) {

                        if (entity->getText() == selectedTextChosen) {

                            itemCh = entity;
                            break;
                        }
                }


                Formula * f = (Formula *)itemCh;

                QListWidgetItem *selectedItem = ui->listWidget_3->currentItem();
                QString selectedText = selectedItem->text();
                EntityBase * itemEx;

                for (EntityBase* entity : all_entities) {

                        if (entity->getText() == selectedText) {
                            itemEx = entity;
                            break;
                        }
                }


                Formula * s = (Formula *)itemEx;

                formula = joinFormula(&all_entities, operation, f, s);
                std::cout<<"Before Emit 2\n";



        }
//        HideCandidates();
        break;
    default:
        break;
    }

    emit update_values(formula);
    this->close();
}

void Or_fun_form::MoveAll(){
    // Move all items from ExistedFormulas to ChoosenFormulas
    int itemCount = ui->ExistedFormulas->count();
    for(int i = 0; i < itemCount; ++i) {
        QListWidgetItem *item = ui->ExistedFormulas->item(0); // Get the first item
        ui->ExistedFormulas->takeItem(0); // Remove the first item from ExistedFormulas
        ui->ChoosenFormulas->addItem(item); // Add the item to ChoosenFormulas
    }

}
void Or_fun_form::DeMoveAll(){
    // Move all items from ExistedFormulas to ChoosenFormulas
    int itemCount = ui->ChoosenFormulas->count();
    for(int i = 0; i < itemCount; ++i) {
        QListWidgetItem *item = ui->ChoosenFormulas->item(0); // Get the first item
        ui->ChoosenFormulas->takeItem(0); // Remove the first item from ExistedFormulas
        ui->ExistedFormulas->addItem(item); // Add the item to ChoosenFormulas
    }
}


void Or_fun_form::MoveOne(){
    QList<QListWidgetItem *> selectedItems = ui->ExistedFormulas->selectedItems();
    foreach(QListWidgetItem *item, selectedItems) {
        QListWidgetItem *newItem = new QListWidgetItem(*item);
        ui->ChoosenFormulas->addItem(newItem);
        delete ui->ExistedFormulas->takeItem(ui->ExistedFormulas->row(item));
    }

}

void Or_fun_form::DeMoveOne(){
    QList<QListWidgetItem *> selectedItems = ui->ChoosenFormulas->selectedItems();
    foreach(QListWidgetItem *item, selectedItems) {
        QListWidgetItem *newItem = new QListWidgetItem(*item);
        ui->ExistedFormulas->addItem(newItem);
        delete ui->ChoosenFormulas->takeItem(ui->ChoosenFormulas->row(item));
    }

}



void Or_fun_form::change_type(int new_type,vector <EntityBase *> _all_entities)
{
    this->type=new_type;
    this->all_entities = _all_entities;
    all_entities[0]->getText().data();
    ui->ExistedFormulas->clear();
    for(int i=0;i<this->all_entities.size();i++){
        new QListWidgetItem(ui->ExistedFormulas);
        auto res = QString::fromStdWString(all_entities[i]->getText().data()).toStdString().c_str();
        QListWidgetItem *___qlistwidgetitem = ui->ExistedFormulas->item(i);

         ___qlistwidgetitem->setText(QCoreApplication::translate("Or_fun_form", res, nullptr));

        EntityBase * base = all_entities.at(i);
        if ( base->getType() == FORMULA_SET )
                 continue;
        Formula * icurr = (Formula *)base;

        icurr = icurr->operationCandidate(&all_entities,(EntityBaseType) type);
    }

    switch (this->type){
    case 0:// AND
        this->setWindowTitle(QCoreApplication::translate("Create AND formula", "Create AND formula", nullptr));
        break;
    case 1:// OR
        this->setWindowTitle(QString("Create OR formula"));
        break;
    case 2:// NOT
        this->setWindowTitle(QCoreApplication::translate("Create NOT formula", "Create NOT formula", nullptr));
        break;
    case 3:// Any
        this->setWindowTitle(QCoreApplication::translate("Set Any formula", "Set Any formula", nullptr));
        break;
    case 4:// Exsits
        this->setWindowTitle(QCoreApplication::translate("Set Exist formula", "Set Exist formula", nullptr));
        break;
    default:
        this->setWindowTitle(QString("doesn't working"));
        break;
    }
}

void Or_fun_form::lang_upd(QTranslator &translator){
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

void Or_fun_form::joinAllFormulas(vector <EntityBase *> * entities, EntityBaseType type)
{
    int k = entities->size();
    int i, j;
    // два связанных цикла, один пробегает от 0 до (всего формул - 2), второй всегда на единицу больше первого, но не больше (всего формул - 1)
    // разыскиваются пары формул (не множеств истинности) и для них предпринимается попытка построить формулу путём объединения типа type
    // если построение возможно, то в newFormula будет ненулевой указатель, тогда полученная формула заносится в entities
    for (i = 0; i < (k - 1); i++)
    {
        EntityBase * first = entities->at(i);
        if ( !first->isFormula() )
            continue;
        for (j = (i + 1); j < k; j++)
        {
            EntityBase * second = entities->at(j);
            if ( !second->isFormula() )
                continue;
            Formula * newFormula = joinFormula(entities, type, (Formula *)first, (Formula *)second );
            if(newFormula)
                entities->push_back(newFormula);
        }
    }
}


Formula * Or_fun_form::joinFormula(vector <EntityBase *> * entities, EntityBaseType type, Formula * first, Formula * second)
{
    Formula * formula;
    int k = entities->size();
    int t, tt, f, ff;
    bool check, check2;
    if ( ( type == AND_OPERATION ) || ( type == OR_OPERATION ) )
    {
        // проверка, существует ли уже заданный элемент с такой операцией и такими родительскими формулами
        check=true;
        for (t = 0; t < k; t++)
        {
            EntityBase * base = entities->at(t);
            if ( !base->isFormula() )
                continue;
            Formula * curr = (Formula *)base;
            if ( curr->getNumberOfParents() >= 2)
            {
//				if ( (curr->getParentLink(0) == first ) && (curr->getParentLink(1) == second ) && (curr->getType() == type ) )
                if ( (get<0>(*curr->getParentLink(0)) == first ) && (get<0>(*curr->getParentLink(1)) == second ) && (curr->getType() == type ) )
                {
                    check=false;
                    break;
                }
            }
//			if ( (first->getType() == QUANTIFIER1_OPERATION) || (first->getType() == QUANTIFIER2_OPERATION) ||
//					(second->getType() == QUANTIFIER1_OPERATION) || (second->getType() == QUANTIFIER2_OPERATION) )
            if ( first->isQuantifier() || second->isQuantifier() )
            {
                check = false;
                break;
            }
        }

        if (check)	// если подобного элемента нет, работаем
        {

            formula = new Formula();
            formula->setType(type);
            formula->setFeature(PERFORMED_FEATURE);

            Formula * icurr = first;
            Formula * jcurr = second;
//			if ( (icurr->quantifierPrefix.compare(_T(" ")) == 0 ) & ( jcurr->quantifierPrefix.compare(_T(" ")) == 0 ) )  //do kv
            if ( !(icurr->isQuantifier() && jcurr->isQuantifier() ))  //do kv
            {
                if ( (icurr->getFeature() == FALSE_FEATURE) & (type == AND_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
                if ( (jcurr->getFeature() == FALSE_FEATURE) & ( type == AND_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
                if ( (icurr->getFeature() == FALSE_FEATURE) & ( type == OR_OPERATION  ) )
                    formula->setFeature(TRUTH_FEATURE);
                if ( (jcurr->getFeature() == FALSE_FEATURE) & ( type == OR_OPERATION ) )
                    formula->setFeature(FALSE_FEATURE);
            }
            // добавляем свободные переменные из родительских формул
            t = icurr->getFreeVariables()->size();
            for (tt = 0; tt < t; tt++)
            {
                EntityVariable * pev = new EntityVariable(*icurr->getFreeVariables()->at(tt));
                formula->getFreeVariables()->push_back(pev);
            }
            f = jcurr->getFreeVariables()->size();
            for (tt = 0; tt < f; tt++)
            {
                check2 = true;
                for (ff = 0; ff < t; ff++)
                {
                    if ( *formula->getFreeVariables()->at(ff) == *jcurr->getFreeVariables()->at(tt) )
//					if ( formula->freeVariables.at(ff)->GetText()->compare(*jcurr->freeVariables.at(tt)->GetText()) == 0 )
                        check2=false;
                }
                if (check2==true)
                {
                    EntityVariable * pev1 = new EntityVariable(*jcurr->getFreeVariables()->at(tt));
                    formula->getFreeVariables()->push_back(pev1);
                }
            }


            ParentLink * elem1 = new ParentLink(icurr, nullptr);
//			formula->parents.push_back(icurr);
            formula->parents.push_back(elem1);
            ParentLink * elem2 = new ParentLink(jcurr, nullptr);
//			formula->parents.push_back(jcurr);
            formula->parents.push_back(elem2);
            formula->putTextOfFormula(entities);
            formula->SetLabel(entities);
        }
    }

    return formula;
}
