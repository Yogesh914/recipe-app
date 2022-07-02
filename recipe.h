#ifndef NEWPROJECT_RECIPE_H
#define NEWPROJECT_RECIPE_H

#include <string>
#include <vector>
#include <iostream>
#include "utility.h"

//Ingredient struct: this struct is used to store the amount and unit of an ingredient
typedef struct Ingredient {
  std::string name;
  Fraction amount;
  std::string unit;

  //extracting ingredient from string
  static struct Ingredient fromString(std::string ingredientStr) {
    //form: amount unit name
    std::regex pattern("\\s*([0-9-/]+)\\s+(\\w+)\\s+(.*)(\\w+)(\\s*$)");
    std::smatch match;
    //Used: https://stackoverflow.com/questions/30921932/understanding-c-regex-by-a-simple-example
    //to help me understand regex more since it is more efficient and shorter in my opinion
    if (std::regex_search(ingredientStr, match, pattern)) {
      std::string amountStr = match[1];
      std::string unitStr = match[2];
      std::string nameStr = match[3];
      nameStr += match[4];
      Ingredient ingredient;
      ingredient.name = nameStr;
      ingredient.amount = Fraction::fromString(amountStr);
      ingredient.amount.adjust();
      ingredient.unit = unitStr;
      return ingredient;
    }

    return Ingredient();
  }

  std::string getName() const {
    return name;
  }

}
Ingredient;

class Recipe {
  public:
    Recipe(std::string name, int servings): name(name), servings(servings) {}

  //Ingredient amount unit name
  void AddIngredient(std::string ingredientStr) {
    ingredients.push_back(Ingredient::fromString(ingredientStr));
  }

  void SetInstructions(std::string instructions) {
    this -> instructions = removeExtraSpaces(instructions);
  }

  std::string IngredientInOneServing(std::string ingredientStr) {
    for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
      if (it -> name == removeExtraSpaces(ingredientStr)) {
        return it -> amount.perServing(servings) + " " + it -> unit + " " + ingredientStr;
      }
    }
    throw std::invalid_argument("Ingredient not found");
  }

  //overloading operator<< for Recipe
  friend std::ostream & operator << (std::ostream & sho, Recipe & r) {
    sho << "Recipe for: " << r.name << std::endl;
    sho << "Serves " << r.servings << std::endl;
    sho << "Ingredients:" << std::endl;
    for (int i = 0; i < r.ingredients.size(); i++) {
      sho << r.ingredients[i].amount.toString() << " " << r.ingredients[i].unit << " " << r.ingredients[i].name << std::endl;
    }
    sho << std::endl;
    sho << "Instructions:" << std::endl;
    sho << r.instructions << std::endl;
    sho << std::endl;
    return sho;
  }

  void ChangeServings(int i) {
    //update the amount of each ingredient
    for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
      it -> amount.changeServings(i, servings);
    }
    servings = i;
  }

  std::string getName() const {
    return name;
  }

  int getServing() const {
    return servings;
  }

  //get a reference to the ingredient equal to the given name
  //returns a reference to the ingredient
  //nullptr if not found
  Ingredient * use(Ingredient ingredient) {
    Ingredient * found = nullptr;
    for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
      if (it -> name == ingredient.name) {
        found = & ( * it);
        break;
      }
    }
    return found;
  }

  private:
    std::string name;
  int servings;
  std::vector < Ingredient > ingredients;
  std::string instructions;
};

#endif //NEWPROJECT_RECIPE_H