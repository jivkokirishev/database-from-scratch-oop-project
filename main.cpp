#include <iostream>

#include "src/collections/Collection.cpp"
#include "src/collections/doubly_linked_list/DoublyLinkedList.cpp"
#include "src/database_components/abstracts/Type.cpp"


#include "src/database_components/implementations/Database.h"


#include "src/database_manager/DbStreamManager.h"
#include "src/database_components/implementations/Integer.h"
#include "src/database_components/implementations/String.h"
#include "src/database_components/implementations/Real.h"

#include "src/database_manager/enums/OperationType.cpp"
#include "src/database_manager/DbFileManager.h"
#include "src/ux_components/CommandParser.h"
#include "src/ux_components/ConsoleLauncher.h"

int main() {
    /// Database creation

    db_components::implementation::Database db = db_components::implementation::Database("Test");

    /// Database file converter creation

    //auto dbFile = db_manager::implementation::DbFileManager(db, std::cout);

    /// Database manager creation

    //db_manager::implementation::DbStreamManager dbManag = db_manager::implementation::DbStreamManager(db, std::cout);

    /// Table addition

    /*db.AddTable("person");
    db.GetTableAt(0).AddColumn(db_components::enums::integerNumber, "id");
    db.GetTableAt(0).AddColumn(db_components::enums::string, "name");

    /// Row creation

    auto row = std::vector<db_components::abstract::Type*>();

    auto id = new db_components::implementation::Integer();
    id->SetValue("13");

    auto name = new db_components::implementation::String();
    name->SetValue("jivko");

    row.push_back(id);
    row.push_back(name);

    /// Row creation

    auto row2 = std::vector<db_components::abstract::Type*>();

    auto id2 = new db_components::implementation::Integer();
    id2->SetValue("132");

    auto name2 = new db_components::implementation::String();
    name2->SetValue("jivko2");

    row2.push_back(id2);
    row2.push_back(name2);

    /// Row insertion

    dbManag.Insert("person", row);

    //name->SetValue("new name");

    dbManag.Insert("person", row2);

    //dbManag.Print("person");

    /// Column insertion

    dbManag.AddColumn("person", "salary", db_components::enums::realNumber);

    auto search = new db_components::implementation::Integer();
    search->SetValue("13");

    //dbManag.Delete("person", 0, *search);

    //dbManag.Print("person");

    /// Row creation

    auto row3 = std::vector<db_components::abstract::Type*>();

    auto id3 = new db_components::implementation::Integer();
    id3->SetValue("1323");

    auto name3 = new db_components::implementation::String();
    name3->SetValue("jivko23");

    auto salary3 = new db_components::implementation::Real();
    salary3->SetValue(2985.029);

    row3.push_back(id3);
    row3.push_back(name3);
    row3.push_back(salary3);

    /// Row insertion

    dbManag.Insert("person", row3);

    //dbManag.Print("person");



    dbManag.Rename("person", "people");



    auto *searchSalary = new db_components::implementation::Real();
    searchSalary->SetIsNullTrue();

    /// Table update

    //auto salary4 = new db_components::implementation::Real();
    //salary4->SetValue(173285.029);

    //dbManag.Update("people", 2, *searchSalary, 2, *salary4);

    /// Select

    //dbManag.Select("people", *searchSalary, 2);

    /// Count

    //dbManag.Count("people", 2, *searchSalary);

    //dbManag.Print("people");

    /// Table creation

    db.AddTable("pAge");

    db.GetTableByName("pAge").AddColumn(db_components::enums::integerNumber, "id");
    db.GetTableByName("pAge").AddColumn(db_components::enums::integerNumber, "age");

    /// Row creation

    auto row21 = std::vector<db_components::abstract::Type*>();

    auto age1 = new db_components::implementation::Integer();
    age1->SetValue(20);

    row21.push_back(id);
    row21.push_back(age1);

    /// Row creation

    auto row22 = std::vector<db_components::abstract::Type*>();

    auto age2 = new db_components::implementation::Integer();
    age2->SetValue(22);

    row22.push_back(id2);
    row22.push_back(age2);

    /// Row insertion

    dbManag.Insert("pAge", row21);
    dbManag.Insert("pAge", row22);

    /// Show tables

    //dbManag.ShowTables();


    //dbManag.Print("people");
    //dbManag.Print("pAge");

    /// Inner Join

    dbManag.Print(dbManag.InnerJoin("people", 0, "pAge", 0));

    /// Aggregate

    dbManag.Aggregate("people", 2, *searchSalary, 0, db_manager::enums::sum);

    /// Save

    dbManag.Save("people_pAge_0_0", "/home/jivko/pAge.csv");*/

    /*dbFile.Load("pAge.csv");

    dbManag.Print("people_pAge_0_0");

    dbManag.AddColumn("people_pAge_0_0", "email", db_components::enums::string);

    dbFile.Save("people_pAge_0_0", "pAge.csv");*/

    //std::string line = "fggfdg 325ergqp \"\\\"ertyryt mvkbn\\\\\\\"\" \"\\\\sdjfd fg\\\"fd,g\" gdfu fffg dfgsu78";
    //std::string line = "fggfdg 325ergqp gdf fdgs cxvrg dgu";

    /*auto splitted = std::vector<std::string>();

    dbFile.SplitString(line, splitted, ",");

    for (auto elem : splitted) {
        std::cout << elem << std::endl;
    }*/


    /*auto splitted = std::vector<std::string>();
    ux_components::CommandParser::Split(line, splitted);

    for(auto elem : splitted) {
        std::cout << elem << std::endl;
    }*/

    auto launcher = ux_components::ConsoleLauncher(db);

    launcher.Run();

    return 0;
}