#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

class Recipe {
public:
    int id;
    int preparationTime;
    int numOfIngredients;
    string name;
    string category;
    string ingredients[5];
    static int nextId;

    Recipe() : preparationTime(0), numOfIngredients(0) {}

    Recipe(int id, int preparationTime, int numOfIngredients, string name, string category, string ingredients[]) {
        this->id = id;
        this->preparationTime = preparationTime;
        this->numOfIngredients = numOfIngredients;
        this->name = name;
        this->category = category;
        for (int i = 0; i < numOfIngredients; ++i) {
            this->ingredients[i] = ingredients[i];
        }
    }

    Recipe(int preparationTime, int numOfIngredients, string name, string category, string ingredients[]) {
        this->id = nextId++;
        this->preparationTime = preparationTime;
        this->numOfIngredients = numOfIngredients;
        this->name = name;
        this->category = category;
        for (int i = 0; i < numOfIngredients; ++i) {
            this->ingredients[i] = ingredients[i];
        }
    }
};

int Recipe::nextId = 1;

Recipe recipeList[100];
int numberOfRecipes = 0;

void viewRecipes() {
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Category" << setw(20) << "Preparation Time" << setw(20) << "Num of Ingredients" << endl;
    cout << "=====================================================================================" << endl;
    for (int i = 0; i < numberOfRecipes; i++) {
        cout << left << setw(5) << recipeList[i].id << setw(20) << recipeList[i].name << setw(20) << recipeList[i].category << setw(20) << recipeList[i].preparationTime << setw(20) << recipeList[i].numOfIngredients << endl;
    }
}

void addRecipe() {
    string name, category;
    int preparationTime;

    cout << " - Enter the Recipe name: ";
    cin >> name;
    cout << " - Enter the Recipe category: ";
    cin >> category;

    cout << " - Enter the Recipe preparation time (in minutes): ";
    cin >> preparationTime;

    cout << " - Enter the number of ingredients (max 5): ";
    int numOfIngredients;
    cin >> numOfIngredients;

    numOfIngredients = (numOfIngredients > 5) ? 5 : numOfIngredients;  // Ensure max 5 ingredients

    string ingredients[5];

    for (int i = 0; i < numOfIngredients; i++) {
        cout << "      - Enter the " << i + 1 << " item in the ingredients list: ";
        cin >> ingredients[i];
    }

    Recipe recipe(preparationTime, numOfIngredients, name, category, ingredients);
    recipeList[numberOfRecipes++] = recipe;
}

void removeRecipe() {
    viewRecipes();
    cout << endl << endl << " - Enter the ID of the Recipe you want to remove: ";
    int recipeId;
    cin >> recipeId;

    int targetIndex = -1;
    for (int i = 0; i < numberOfRecipes; ++i) {
        if (recipeList[i].id == recipeId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex != -1) {
        for (int i = targetIndex; i < numberOfRecipes - 1; ++i) {
            recipeList[i] = recipeList[i + 1];
        }
        numberOfRecipes--;
        cout << "Recipe " << recipeId << " deleted successfully." << endl;
    }
    else {
        cout << "Recipe " << recipeId << " not found." << endl;
    }
}

void searchRecipe() {
    cout << " - Enter the ID of the Recipe you want to search: ";
    int recipeId;
    cin >> recipeId;

    int targetIndex = -1;
    for (int i = 0; i < numberOfRecipes; ++i) {
        if (recipeList[i].id == recipeId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex != -1) {
        cout << "ID : " << recipeList[targetIndex].id << endl;
        cout << "Name : " << recipeList[targetIndex].name << endl;
        cout << "Category : " << recipeList[targetIndex].category << endl;
        cout << "Preparation Time : " << recipeList[targetIndex].preparationTime << endl;
        cout << "Ingredients : " << endl;
        for (int i = 0; i < recipeList[targetIndex].numOfIngredients; i++) {
            cout << i + 1 << ". " << recipeList[targetIndex].ingredients[i] << endl;
        }
    }
    else {
        cout << "Recipe " << recipeId << " not found." << endl;
    }
}

void updateRecipe() {
    cout << " - Enter the ID of the Recipe you want to update: ";
    int recipeId;
    cin >> recipeId;

    int targetIndex = -1;
    for (int i = 0; i < numberOfRecipes; ++i) {
        if (recipeList[i].id == recipeId) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex != -1) {
        string newName, newCategory;
        int newPreparationTime;

        cout << " - Enter the Recipe name: ";
        cin >> newName;
        cout << " - Enter the Recipe category: ";
        cin >> newCategory;

        cout << " - Enter the Recipe preparation time (in minutes): ";
        cin >> newPreparationTime;

        cout << " - Enter the number of ingredients (max 5): ";
        int newNumOfIngredients;
        cin >> newNumOfIngredients;
        newNumOfIngredients = (newNumOfIngredients > 5) ? 5 : newNumOfIngredients;  // Ensure max 5 ingredients

        string newIngredients[5];

        for (int i = 0; i < newNumOfIngredients; i++) {
            cout << "      - Enter the " << i + 1 << " item in the ingredients list: ";
            cin >> newIngredients[i];
        }

        Recipe newRecipe(newPreparationTime, newNumOfIngredients, newName, newCategory, newIngredients);
        recipeList[targetIndex] = newRecipe;
    }
    else {
        cout << "Recipe " << recipeId << " not found." << endl;
    }
}

void suggestRecipe() {
    srand(time(0));
    int randomIndex = rand() % numberOfRecipes;

    cout << "ID : " << recipeList[randomIndex].id << endl;
    cout << "Name : " << recipeList[randomIndex].name << endl;
    cout << "Category : " << recipeList[randomIndex].category << endl;
    cout << "Preparation Time : " << recipeList[randomIndex].preparationTime << endl;
    cout << "Ingredients : " << endl;
    for (int i = 0; i < recipeList[randomIndex].numOfIngredients; i++) {
        cout << i + 1 << ". " << recipeList[randomIndex].ingredients[i] << endl;
    }
}

void save() {
    ofstream outFile("data.txt");

    outFile << numberOfRecipes << endl;

    for (int i = 0; i < numberOfRecipes; i++) {
        outFile << recipeList[i].id << " " << recipeList[i].preparationTime << " " << recipeList[i].numOfIngredients << " " << recipeList[i].name << " " << recipeList[i].category ;

        for (int j = 0; j < recipeList[i].numOfIngredients; j++) {
            outFile << " " << recipeList[i].ingredients[j] ;
        }

        cout << endl;
    }
    outFile.close();
}

void getFromFile() {
    ifstream inFile("data.txt");
    if (inFile.is_open()) {
        inFile >> numberOfRecipes;

        int id;
        int preparationTime;
        int numOfIngredients;
        string name;
        string category;
        string ingredients[5];

        for (int i = 0; i < numberOfRecipes; i++) {
            inFile >> id >> preparationTime >> numOfIngredients >> name >> category;

            for (int j = 0; j < numOfIngredients; j++) {
                inFile >> ingredients[j];
            }

            cout << endl;
            Recipe r = Recipe(id, preparationTime, numOfIngredients, name, category, ingredients);
            recipeList[i] = r;
        }
    }
    inFile.close();
}

void mainMenu() {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                                         |" << endl;
    cout << "|       Recipe Management System          |" << endl;
    cout << "|       -------------------------         |" << endl;
    cout << "|                                         |" << endl;
    cout << "|            1. View Recipes              |" << endl;
    cout << "|            2. Add Recipe                |" << endl;
    cout << "|            3. Remove Recipe             |" << endl;
    cout << "|            4. Update Recipe             |" << endl;
    cout << "|            5. Search a Recipe           |" << endl;
    cout << "|            6. Suggest a Recipe          |" << endl;
    cout << "|            7. Exit                      |" << endl;
    cout << "|                                         |" << endl;
    cout << "+-----------------------------------------+" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        viewRecipes();
        break;
    case 2:
        addRecipe();
        break;
    case 3:
        removeRecipe();
        break;
    case 4:
        updateRecipe();
        break;
    case 5:
        searchRecipe();
        break;
    case 6:
        suggestRecipe();
        break;
    default:
        save();
        exit(0);
        cout << "Invalid option. Please try again." << endl;
        break;
    }
    mainMenu();
}

int main() {
    getFromFile();
    mainMenu();
}
