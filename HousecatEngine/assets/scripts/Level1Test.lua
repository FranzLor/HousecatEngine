-----------------------------------------------
--            LUA SCRIPT TEST                --
-----------------------------------------------


--define your LEVEL as a table
Level = {
    ----------------------------------------------------
    --              ASSETS for your game              --
    ----------------------------------------------------
    assets = {
        [0] =
        --TODO
        { type = "texture", id = "player", file = "./assets/textures/cat_sprite_2.png" },
        { type = "texture", id = "npc", file = "./assets/textures/cat_sprite.png" },


        { type = "texture", id = "ghost", file = "./assets/textures/ghost.png" },
        { type = "texture", id = "slime", file = "./assets/textures/slime.png" },


        { type = "texture", id = "treeA", file = "./assets/textures/treeA.png" },
        { type = "texture", id = "treeB", file = "./assets/textures/treeB.png" },
        { type = "texture", id = "treeC", file = "./assets/textures/treeC.png" },


        { type = "texture", id = "tilemap-texture", file = "./assets/tilemaps/terrain_tile.png" },

        { type = "font", id = "roboto", file = "./assets/fonts/roboto.regular.ttf", font_size = 18 },
        { type = "font", id = "montserrat", file = "./assets/fonts/montserrat.bold.ttf", font_size = 20 }
    },

    ----------------------------------------------------
    --              MAP CONFIG for game               --
    ----------------------------------------------------
    tilemap = {
        mapFilePath = "./assets/tilemaps/Map1.map",
        textureID = "tilemap-texture",
        tileSize = 32,
        tileScale = 2.0,
        tileCols = 35,
        tileRows = 40
    },

    ----------------------------------------------------
    --       ENTITIES and COMPONENTS for game         --
    ----------------------------------------------------
    entities = {
        [0] =
        --PLAYER
        {
            tag = "player",
            components = {
                userControl = {
                    up = { x = 0, y = -500 },
                    right = { x = 500, y = 0 },
                    down = { x = 0, y = 500 },
                    left = { x = -500, y = 0 }
                },

                transform = {
                    position = { x = 180, y = 500 },
                    scale = { x = 4.0, y = 4.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "player",
                    width = 32,
                    height = 32,
                    zIndex = 2,
                    fixed = false,
                    srcRectX = 0,
                    srcRectY = 0
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },

                animation = {
                    numFrames = 4,
                    frameSpeed = 5
                },

                movementState = {
                    isMoving = false
                },

                boxcollider = {
                    width = 22,
                    height = 20,
                    offset = { x = 20.0, y = 24.0 }
                },

                health = {
                    healthPercent = 100
                },

                camera = {
                    follow = true
                }
            }
        },

        --ENEMY
        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 540, y = 400 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 4
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },

                animation = {
                    numFrames = 8,
                    frameSpeed = 10
                },

                movementState = {
                    isMoving = true
                },

                boxcollider = {
                    width = 22,
                    height = 20,
                    offset = { x = 20.0, y = 24.0 }
                },

                health = {
                    healthPercent = 100
                },

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        --ENEMY
        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 800, y = 400 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 4
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },

                animation = {
                    numFrames = 10,
                    frameSpeed = 6
                },

                movementState = {
                    isMoving = true
                },

                boxcollider = {
                    width = 22,
                    height = 20,
                    offset = { x = 20.0, y = 24.0 }
                },

                health = {
                    healthPercent = 100
                },

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        --TREE A
        {
            group = "tree",
            components = {
                transform = {
                    position = { x = 1000, y = 300 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 7
                },

                boxcollider = {
                    width = 64,
                    height = 96,
                    offset = { x = 0.0, y = 0.0 }
                }

            }
        }


    }
} 