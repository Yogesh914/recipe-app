# recipe-app
Header-only library that defines a class that can hold recipes and a class that represents a (extremely) simple recipe app.

- recipe.h: This header file contains the declaration and definition of a class named Recipe.

Example:
~~~
  Recipe r("Microwave Popcorn", 3);
  r.AddIngredient("1/2 cup unpopped popcorn");
  r.AddIngredient("1 teaspoon vegetable oil");
  r.AddIngredient("1/2 teaspoon salt");
  r.SetInstructions(
      R"***(In a cup or small bowl, mix together the unpopped popcorn and oil. 
  Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt. 
    Fold the top of the bag over twice to seal in the ingredients. 

  Cook in the microwave at full power for 2 1/2 to 3 minutes, 
   or until you hear pauses of about 2 seconds between pops. 

  Carefully open the bag to avoid steam, and pour into a serving bowl. 
  From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/
  )***");

  std::cout << r << std::endl;

  std::ostringstream oss;
  oss << r;
  std::string expected = R"***(Recipe for: Microwave Popcorn
Serves 3
Ingredients:
1/2 cup unpopped popcorn
1 teaspoon vegetable oil
1/2 teaspoon salt

Instructions:
In a cup or small bowl, mix together the unpopped popcorn and oil.
Pour the coated corn into a brown paper lunch sack, and sprinkle in the salt.
Fold the top of the bag over twice to seal in the ingredients.
Cook in the microwave at full power for 2 1/2 to 3 minutes,
or until you hear pauses of about 2 seconds between pops.
Carefully open the bag to avoid steam, and pour into a serving bowl.
From: https://www.allrecipes.com/recipe/87305/microwave-popcorn/

)***";

  std::cout << expected << std::endl;

  assert(oss.str() == expected);

  std::cout << r.IngredientInOneServing("unpopped popcorn") << std::endl;

  std::cout << "Changing servings to 6" << std::endl;
  r.ChangeServings(6);

  std::cout << r << std::endl;
~~~

- app.h: This header file needs to contain the declaration and definition of a class named RecipeApp. 

Example:
~~~
  RecipeApp ra;
  Recipe simple_pop("Simple Popcorn", 1);
  simple_pop.AddIngredient("1/4 cup unpopped popcorn");
  simple_pop.AddIngredient("1/4 teaspoon vegetable oil");
  simple_pop.AddIngredient("1/4 teaspoon salt");
  simple_pop.SetInstructions(R"***(Pop it!)***");

  Recipe apples("An Apple", 3);
  apples.AddIngredient("1-5/6 unit apple");
  apples.SetInstructions(R"***(Grab it!)***");

  ra.AddRecipe(simple_pop);
  ra.AddRecipe(apples);
  ra.AddIngredientToPantry("2 cup unpopped popcorn");
  ra.AddIngredientToPantry("4-7/8 unit apple");
  std::cout << ra << std::endl;

  Recipe r = ra.UseUpIngredient("10 unit apple");
  std::cout << "Using up apples" << std::endl;
  std::cout << r;

  std::cout << ra;
~~~

- utility.h: Contains other funtions and classes that are used


