#ifndef PROJECT_APP_H
#define PROJECT_APP_H

#include "recipe.h"
#include <bits/stdc++.h>
#include <algorithm>

class RecipeApp {
  public:
    RecipeApp() {
      ;
    }

  void AddRecipe(Recipe recipe) {
    recipes.push_back(recipe);
  }

  void AddIngredientToPantry(const char * string) {
    pantry.push_back(Ingredient::fromString(string));
  }

  //overload operator<< for RecipeApp
  friend std::ostream & operator << (std::ostream & os,
    const RecipeApp & recipeApp) {
    os << "Recipes in the app (ordered by name):" << std::endl;

    std::vector < Recipe > sortedRecipes = recipeApp.recipes;
    std::sort(sortedRecipes.begin(), sortedRecipes.end(), [](const Recipe & a,
      const Recipe & b) {
      return a.getName() < b.getName();
    });

    for (auto recipe: sortedRecipes) {
      os << recipe;
    }

    //sort ingredients in pantry by name
    std::vector < Ingredient > sortedPantry = recipeApp.pantry;
    std::sort(sortedPantry.begin(), sortedPantry.end(), [](const Ingredient & a,
      const Ingredient & b) {
      return a.getName() < b.getName();
    });

    os << "Ingredients in pantry (ordered by name):" << std::endl;
    for (auto ingredient: sortedPantry) {
      os << ingredient.amount.toString() << " " << ingredient.unit << " " << ingredient.name << std::endl;
    }

    return os;

  }

  Recipe UseUpIngredient(const char * string) {
    Ingredient ingredient = Ingredient::fromString(string);
    std::vector < Recipe > sortedRecipes = recipes;

    //sort recipes by name
    //we use the std::sort from the cpp STL to sort the recipes by name 
    //and a lambda function to compare the names as predicates
    //ref: https://en.cppreference.com/w/cpp/algorithm/sort
    //ref: https://en.cppreference.com/w/cpp/language/lambda
    std::sort(sortedRecipes.begin(), sortedRecipes.end(), [](const Recipe & a,
      const Recipe & b) {
      return a.getName() < b.getName();
    });

    //search for a recipe that use the specified ingredient in sortedRecipes by name
    for (auto recipe: sortedRecipes) {
      Ingredient * ing = recipe.use(ingredient);
      if (ing != nullptr) {
        /*
            the formual used in this function is:
                     U1 = numerator1 / denominator1   ----->    serving1
            alpha >= U2 = numerator2 / denominator2   ----->    newServing
            we search U2 and serving2 such that alpha >= U2
            and we have the following equation:
            UnewServing = numerator2 *denominator1 *serving1 / (numerator1 * denominator2) 
            !using interger division
        
        */
        int numerator1, denominator1, numerator2, denominator2;
        ing -> amount.toNumeratorAndDenominator(numerator1, denominator1);
        ingredient.amount.toNumeratorAndDenominator(numerator2, denominator2);
        int newServings = (numerator2 * denominator1 * recipe.getServing()) / (numerator1 * denominator2);
        Recipe newRecipe = recipe;
        newRecipe.ChangeServings(newServings);
        return newRecipe;
      }
    }

    throw std::invalid_argument("Ingredient not found");
  }

  private:
    std::vector < Recipe > recipes;
    std::vector < Ingredient > pantry;

};

#endif //PROJECT_APP_H