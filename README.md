![Housecat banner](https://github.com/FRLor/Housecat/assets/160707192/3004f416-ce51-49d0-aa01-1706a56d6407)

`Housecat` is a lightweight and modular game engine designed to provide developers with a flexible and efficient framework for building 2D games. 
At its core, it utilizes the Entity-Component-System (ECS) architecture, offering easier game object management and allowing for easy scalability and extensibility.
The engine offers developers a game project, that shows off the engine's capabilities and potential. It also offers a simple 2D level Editor, to help developers build their game projects.

![Static Badge](https://img.shields.io/badge/In%20Development-darkgreen?style=flat) &nbsp; ![Static Badge](https://img.shields.io/badge/version-v1.0-blue?style=flat)


# Table of Contents
1. [Intro](#intro)
   - [Get Started](#get-started)
   - [How to Use](#how-to-use)
   - [Examples](#examples)
2. [Features](#features)
3. [Documentation](#documentation)
4. [Contributions](#contributions)
5. [License](#license)
   
# Intro
This engine was crafted to streamline the process of game development, especially for indie developers and small teams. Entity-Component-System (ECS) design pattern to decouple game logic and state representation, enabling flexible interaction and greater ease in maintaining, modifying, or extending complex game functionalities.
This architectural approach emphasizes in a more manageable and scalable code, which is beneficial in games with numerous interactive elements and systems.<br/><br/>
Want to learn more about the ECS paradigm? I recommend these links that got me started: 
- [ECS Game Engine Design (Daniel Hall, Cal Poly)](https://digitalcommons.calpoly.edu/cgi/viewcontent.cgi?article=1138&context=cpesp)
- [The Entity-Component-System - An awesome game-design pattern in C++ (Tobias Stein, Game Developer)](https://www.gamedeveloper.com/design/the-entity-component-system---an-awesome-game-design-pattern-in-c-part-1-)
- [Entity Component System: An Introductory Guide (John Terra, Simplilearn)](https://www.simplilearn.com/entity-component-system-introductory-guide-article)
  
 ## Get Started
To get started with Housecat, follow these steps:
- Clone the Housecat repository to your local machine.<br/>
  ```git clone https://github.com/FRLor/Housecat.git```
- Build the engine using the provided build instructions. (Refer to Appendix B, C, and D of Documentation)
- Start creating your game using the Housecat framework and editor.
   
 ## How to Use
`Housecat` offers a straightforward approach to game development:
- Define your game entities and components using the engine's robust ECS.
- Utilize the Housecat Editor to design levels, manage assets, and script events.
- Use the Asset Manager to easily handle game assets.
- Incorporate custom behaviors and game logic with Lua scripting.

## Examples
### Using the Lua Script and LevelManager

This example demonstrates how to leverage `Housecat`'s LevelManager and Lua Scripting to dynamically load and configure game levels, streamlining the game setup process.<br/><br/>

**Initialize the Game and Load the Lua Script:**
First, ensure that the game environment, including SDL, the Housecat ECS, and other systems, are initialized. Then, load the Lua script which contains the game's configuration, assets, and level design:<br/>
```
Game game;
game.Initialize();
game.levelManager->LoadLevel(game.housecat, game.renderer, game.assetManager, game.lua, 1);
```

**Load Assets Using Lua Table Definitions:**
The Lua script defines all assets and their properties, which the LevelManager reads to load textures, fonts, and other resources:<br/>
```
Level = {
    assets = {
        { type = "texture", id = "tileset", file = "./assets/textures/tileset.png" },
        { type = "font", id = "main_font", file = "./assets/fonts/roboto.ttf", font_size = 16 },
        { type = "sound", id = "background_music", file = "./assets/sounds/background.wav" }
    }
}
```

**Configure the Level from Lua Script:**
Utilize the Lua script to specify the layout, entities, and interactions within the level:<br/>
```
Level.tilemap = {
    mapFilePath = "./assets/levels/level1.map",
    textureID = "tileset",
    tileSize = 32,
    tileScale = 2.0
}
```

**Instantiate Entities Defined in Lua:**
Create game entities using the configurations specified in the Lua script. Each entity's components and behaviors can be customized through Lua:<br/>
```
Level.entities = {
    {
        tag = "player",
        components = {
            transform = { position = { x = 100, y = 150 }, scale = { x = 2.0, y = 2.0 }},
            sprite = { textureID = "player_texture", width = 32, height = 32 },
            movement = { speed = 200 }
        }
    }
}
```

**Read and Apply Entity Components from Lua:**
Instantiation of entities and their components involves parsing Lua tables to dynamically assign attributes and functionalities, as demonstrated here:<br/>
```
sol::table entities = lua["Level"]["entities"];
for (auto& entity : entities) {
    Entity newEntity = game.housecat->CreateEntity();
    if (entity["tag"]) {
        newEntity.Tag(entity["tag"]);
    }
    if (entity["components"]["transform"]) {
        newEntity.AddComponent<TransformComponent>(
            glm::vec2(entity["components"]["transform"]["position"]["x"], entity["components"]["transform"]["position"]["y"]),
            glm::vec2(entity["components"]["transform"]["scale"]["x"], entity["components"]["transform"]["scale"]["y"]),
            entity["components"]["transform"]["rotation"]
        );
    }
    // Additional components like SpriteComponent, UserControlComponent, etc., are added similarly
}
```
<br/><br/>


### Without the Lua Script and LevelManager
This first example demonstrates how to create a simple 2D game using `Housecat`'s features, showcasing the setup of a basic game environment, entity creation, and game loop management.<br/><br/>

**Initialize the Game Environment:**
Start by setting up the SDL library, creating a window, and preparing the renderer. Initialize the Housecat ECS framework to manage game entities and components:
```
Game game;<br/>
game.Initialize();<br/>
```

**Load Game Assets:**
Before creating entities, load all necessary textures, fonts, and sounds using the AssetManager. This ensures that all game resources are available for use:
```
game.assetManager->AddTexture(game.renderer, "playerTexture", "assets/textures/player.png");<br/>
game.assetManager->AddFont("roboto", "assets/fonts/roboto.regular.ttf", 16);<br/>
game.assetManager->AddSound("jumpSound", "assets/sounds/jump.wav");<br/><br/>
```

**Create Game Entities:**
Create entities such as a player and attach necessary components to them. Components define the properties and behavior of entities:
```
Entity player = game.housecat->CreateEntity();<br/>
player.AddComponent<TransformComponent>(Vector2(100, 100), Vector2(1.0f, 1.0f), 0.0f);<br/>
player.AddComponent<SpriteComponent>("playerTexture", 32, 32);<br/>
player.AddComponent<UserControlComponent>();<br/><br/>
```
<br/>

### Call Housecat to Grab Necessary Systems and Updates
Once your game setup is complete and all resources are loaded, you can begin managing the game logic and rendering by integrating the engine's systems. To handle the rendering of entities, you must first add the necessary systems to your `Housecat` instance and then periodically update them in your game loop.<br/>

**Add Necessary Systems:**
Before starting the game loop, ensure all relevant systems are registered with `Housecat`. This includes systems for rendering, input handling, physics, animations, and any other functionalities your game requires:<br/>
```
housecat->AddSystem<RenderSystem>();
housecat->AddSystem<MovementSystem>();
housecat->AddSystem<CollisionSystem>();
```
**Update Systems in Game Loop:**
Within your game's main loop, call the update methods on each system to process all entities and their components.
```
housecat->GetSystem<MovementSystem>().Update(deltaTime);
housecat->GetSystem<CollisionSystem>().Update();
housecat->GetSystem<RenderSystem>().Update(game.renderer, game.assetManager, game.camera);
```
<br/><br/>

# Features
This repository comes with three main features right off the bat: the `Housecat` game engine itself, the level Editor, and a Game project.<br/>
Here is a list of the features that this project has to offer to game developers:
- **ECS Core Architecture:**
  - Efficient Entity Management: Entities are lightweight identifiers that allow for flexible management and combination of gameplay components.
  - Modular Component System: Encourages reusable code and data-driven design, making it easier to add new types of behaviors or features without altering existing systems.
  - Dynamic System Interaction: Systems operate on components, making it easy to define complex interactions in a highly decoupled manner.
    
- **Level Editor:**
  - **Level Design Tools:** Tools for creating and modifying game levels and design directly within the editor.
  - **Asset Management Integration:** Seamlessly import, organize, and manage game assets within the editor.
  - **ImGui-Powered UI:** Utilizes ImGui to create a user-friendly, responsive, and highly customizable editor interface, enhancing the overall development experience.
  - **FontAwesome6 Icons:** Integrates FontAwesome6 to style the UI with scalable icons, improving visual clarity and aesthetic appeal of the editor's interface.
 
- **Cat Game:**
  - **2D Game:** Showcases the capabilities of the `Housecat` game engine through an engaging and developed 2D game.
  - **Customizable Gameplay:** Developers can extend and customize the game using Lua script, allowing for dynamic gameplay changes and enhancements.
  - **Integrated Level Management:** Utilizes the LevelManager system for seamless level transitions and management.
  - **Educational Resource:** Serves as a practical example for developers to learn how to utilize various aspects of the Housecat game engine in a real-world scenario.

- **Housecat Manager / Registry:**
  - **Entity Lifecycle Management:** Calling `Housecat` simplifies the creation, modification, and destruction of entities within your game project.
  - **Tagging and Grouping:** Allows entities to be tagged or grouped for efficient querying and batch operations.

- **Asset Manager:**
  - **Resource Loading:** Manage loading and unloading of assets such as textures, fonts, sounds, and scripts to optimize memory usage.
  - **Asset Caching:** Uses SDL by implementing caching mechanisms to speed up asset retrieval and reduce load times.
  - **Extensible for Various Asset Types:** Easily extendable to support new asset types as needed by the game.

- **Event Manager:**
  - **Subscriber-Listener Paradigm:** Employs a subscriber-listener design to manage interactions within the game engine, allowing components to subscribe to and listen for specific events without direct coupling.
  - **Custom Event Types:** Enables developers to define and trigger custom events tailored to their game's needs, enhancing the flexibility of game mechanics and interactions.
  - **Efficient Event Handling:** Optimizes event processing, including support for asynchronous handling, to improve responsiveness and reduce performance overhead.

- **Lua Script Integration:**
  - **Flexible Scripting with Lua:** Leverages Lua to define game elements and behaviors dynamically through scripts. Developers can use Lua to define asset tables, set up game entities, and script complex interactions.
  - **Dynamic Behavior Modification:** Facilitates runtime changes to game logic and entity behavior without recompilation, supporting dynamic binding through the script system. This allows for on-the-fly adjustments and rapid iteration.
  - **API Access:** Provides Lua scripts with extensive access to the game engine's API, enabling direct manipulation of entities and components, offering more creative freedom and control over game mechanics.

- **Modular Rendering System:**
  - **2D Graphics Support:** Built primarily for 2D game development, utilizing SDL2 for rendering sprites, textures, and animations efficiently.
  - **Culling and Optimization:** Implements culling to only render entities visible in the camera's viewport, optimizing processing and rendering load.
  - **Text Rendering:** Supports text rendering using SDL_ttf, allowing for dynamic text displays within the game, ideal for UI elements and game notifications.

- **Input Management:**
  - **SDL Integration for Input Handling:** Leverages SDL for comprehensive input management, capturing events from keyboards and mice for responsive gameplay.
  - **ECS-Driven Event Handling:** Utilizes the ECS architecture to dispatch input-related events, ensuring seamless integration with game entity behaviors and state changes.
 
- **Logger:**
  - **Comprehensive Logging:** Provides a robust logging system that captures a wide range of information including debug messages, warnings, and errors.
  - **Real-Time Feedback:** Enables real-time logging feedback in the console, helping developers to quickly identify and resolve issues during development.
  - **Severity Levels:** Supports different levels of log severity (info, warning, error, debug), allowing developers to filter logs based on their current needs.
  - **Integration with Editor:** Fully integrated within the Housecat Editor, facilitating a seamless development experience by providing immediate access to logs directly within the development environment.


# Documentation
The `Housecat` Wiki page is still in development. But it's worth checking out for updates!<br/>
[Housecat Wiki](https://github.com/FRLor/Housecat/wiki).<br/><br/>
The wiki will help you get the most out of the engine and streamline your game development process.<br/>

For those who want to get started right away, in the Source folder, each file will contain Documentation on its purpose, usage, and other useful commentary.


# Contributions
   Any contributions to improve and extend `Housecat` are all welcome!<br/><br/>
   However, I cannot guarantee that each contribution will be accepted.<br/>
   If you have any requests for more features, bug fixes, and even constructive criticism, feel free to DM me through my [GitHub](https://github.com/FRLor).


# License
   `Housecat` is licensed under the MIT License. See the [MIT License](https://github.com/FRLor/Housecat/blob/master/LICENSE.txt) file for more information.<br/><br/>
   Each asset used for the Cat Game project were all free and downloaded from [itch.io](https://itch.io/). The owners granted expressive use for their respective assets.
   However, I have also provided some of their Licenses, that were provided, as a way to credit their 
 creative work.
