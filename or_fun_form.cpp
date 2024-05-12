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

//    this->resize(800, 600);
//    name_label = new QLabel(this);
//    name_label->setObjectName(QString::fromUtf8("name_label"));
//    name_label->setGeometry(QRect(20, 20, 181, 18));
//    left_listView = new QListView(this);
//    left_listView->setObjectName(QString::fromUtf8("left_listView"));
//    left_listView->setGeometry(QRect(0, 100, 321, 461));
//    force_right_Button = new QPushButton(this);
//    force_right_Button->setObjectName(QString::fromUtf8("force_right_Button"));
//    force_right_Button->setGeometry(QRect(350, 70, 31, 26));
//    right_Button = new QPushButton(this);
//    right_Button->setObjectName(QString::fromUtf8("right_Button"));
//    right_Button->setGeometry(QRect(350, 100, 31, 26));
//    left_Button = new QPushButton(this);
//    left_Button->setObjectName(QString::fromUtf8("left_Button"));
//    left_Button->setGeometry(QRect(350, 130, 31, 26));
//    force_left_Button = new QPushButton(this);
//    force_left_Button->setObjectName(QString::fromUtf8("force_left_Button"));
//    force_left_Button->setGeometry(QRect(350, 160, 31, 26));
//    upper_listView = new QListView(this);
//    upper_listView->setObjectName(QString::fromUtf8("upper_listView"));
//    upper_listView->setGeometry(QRect(410, 50, 381, 241));
//    to_all_formulas_radioButton = new QRadioButton(this);
//    to_all_formulas_radioButton->setObjectName(QString::fromUtf8("to_all_formulas_radioButton"));
//    to_all_formulas_radioButton->setGeometry(QRect(20, 50, 291, 24));
//    bin_radioButton = new QRadioButton(this);
//    bin_radioButton->setObjectName(QString::fromUtf8("bin_radioButton"));
//    bin_radioButton->setGeometry(QRect(20, 70, 102, 24));
//    low_listView = new QListView(this);
//    low_listView->setObjectName(QString::fromUtf8("low_listView"));
//    low_listView->setGeometry(QRect(410, 320, 381, 241));
//    perform_to_all_list_radioButton = new QRadioButton(this);
//    perform_to_all_list_radioButton->setObjectName(QString::fromUtf8("perform_to_all_list_radioButton"));
//    perform_to_all_list_radioButton->setGeometry(QRect(410, 293, 271, 31));
//    perform_Button = new QPushButton(this);
//    perform_Button->setObjectName(QString::fromUtf8("perform_Button"));
//    perform_Button->setGeometry(QRect(610, 570, 80, 26));
//    cancel_Button = new QPushButton(this);
//    cancel_Button->setObjectName(QString::fromUtf8("cancel_Button"));
//    cancel_Button->setGeometry(QRect(710, 570, 80, 26));

//    this->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
//    name_label->setText(QCoreApplication::translate("Form", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\321\217 \320\276\320\261\321\212\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217 V", nullptr));
//    force_right_Button->setText(QCoreApplication::translate("Form", ">>", nullptr));
//    right_Button->setText(QCoreApplication::translate("Form", ">", nullptr));
//    left_Button->setText(QCoreApplication::translate("Form", "<", nullptr));
//    force_left_Button->setText(QCoreApplication::translate("Form", "<<", nullptr));
//    to_all_formulas_radioButton->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216 \320\272\320\276 \320\262\321\201\320\265\320\274 \321\204\320\276\321\200\320\274\321\203\320\273\320\260\320\274", nullptr));
//    bin_radioButton->setText(QCoreApplication::translate("Form", "\320\221\320\270\320\275\320\260\321\200\320\275\320\260\321\217", nullptr));
//    perform_to_all_list_radioButton->setText(QCoreApplication::translate("Form", "\320\237\321\200\320\270\320\274\320\265\320\275\321\217\321\202\321\214 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\321\216 \320\272\320\276 \320\262\321\201\320\265\320\274\321\203 \321\201\320\277\320\270\321\201\320\272\321\203", nullptr));
//    perform_Button->setText(QCoreApplication::translate("Form", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
//    cancel_Button->setText(QCoreApplication::translate("Form", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));

//    QMetaObject::connectSlotsByName(this);

    QObject::connect(ui->MoveOne, SIGNAL(clicked()), this, SLOT(MoveOne()));
    QObject::connect(ui->DemoveOne, SIGNAL(clicked()), this, SLOT(DeMoveOne()));
    QObject::connect(ui->MoveAll, SIGNAL(clicked()), this, SLOT(MoveAll()));
    QObject::connect(ui->DemoveAll, SIGNAL(clicked()), this, SLOT(DeMoveAll()));

    QObject::connect(ui->ChoosenFormulas, &QListWidget::itemSelectionChanged, this, &Or_fun_form::moveAllToThirdList);



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

    // Move all items from ChoosenFormulas and ExistedFormulas to listWidget_3 except the selected item
    int choosenItemCount = ui->ChoosenFormulas->count();
    for(int i = 0; i < choosenItemCount; ++i) {
        QListWidgetItem *item = ui->ChoosenFormulas->item(i);
        if (item != selectedItem) {
            ui->listWidget_3->addItem(item->clone());
        }
    }

    int existedItemCount = ui->ExistedFormulas->count();
    for(int i = 0; i < existedItemCount; ++i) {
        QListWidgetItem *item = ui->ExistedFormulas->item(i);
        if (item != selectedItem) {
            ui->listWidget_3->addItem(item->clone());
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


                //all_entities[i]->getText().data()
//                if(selectedItem)
//                {
//                    SemanticString * dsi = (SemanticString *) m_ListBoxDestination1.DCU.at(selected);
//                    Formula * f = (Formula *)dsi->formula;
//                    if(f)
//                    {
//                        Formula * formula = f->negativeFormula(allEntities);
//                        if (!formula) {
//                            if (CURRENT_LANG_OF == "rus") {
//                                MessageBox(_T("Формула с такими же переменными уже существует и не может быть создана"), _T("Предупреждение"), MB_OK);
//                            }
//                            else {
//                                MessageBox(_T("A formula with the same variables already exists and cannot be created"), _T("Warning"), MB_OK);

//                            }
//                        }
//                    }
//                }


            }
        }
        break;
//    case QUANTIFIER1_OPERATION:
//    case QUANTIFIER2_OPERATION:
//        if(m_CheckApplyForAll.GetCheck())
//        {
//            if(formulas->size() > 0)
//                quantifierAllFormulas(allEntities, operation);
//        }
//        else
//        {
//            int selected = m_ListBoxDestination1.GetCurSel();
//            if(selected >= 0)
//            {
//                SemanticString * dsi = (SemanticString *) m_ListBoxDestination1.DCU.at(selected);
//                Formula * f = (Formula *)dsi->formula;
//                if(f)
//                {
//                    if ( m_checkAll2.GetCheck() )
//                    {
//                        for ( size_t i = 0; i < f->possibleVariables.size(); i++)
//                        {
//                            EntityVariable * pev = f->possibleVariables.at(i);
//                            f->quantifierFormula(allEntities, operation, pev);
//                        }
//                    }
//                    else
//                    {
//                        int selected1 = m_ListBoxDestination2.GetCurSel();
//                        if(selected1 >= 0)
//                        {
//                            EntityVariable * pev = f->possibleVariables.at(selected1);
//                            f->quantifierFormula(allEntities, operation, pev);
//                        }
//                    }
//                }
//            }
//        }
//        HideFreeVariables();
//    break;

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
                std::cout<<"Before Emit 3\n";
                // При дебагинге не правильно работает s(itemEx) и также не добавляются новые entities
                formula = joinFormula(&all_entities, operation, f, s);
                std::cout<<"Before Emit 2\n";
//                if ( formula != nullptr )
//                    all_entities.push_back(formula);



        }
//        HideCandidates();
        break;
    default:
        break;
    }
    std::cout<<"Before Emit\n";
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
    default:
        this->setWindowTitle(QString("ne robit!!"));
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
