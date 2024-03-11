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
        { type = "texture", id = "ghost", file = "./assets/textures/ghost.png" },

        { type = "texture", id = "map", file = "./assets/tilemaps/tilemap.png" },

        { type = "font", id = "roboto", file = "./assets/fonts/roboto.regular.ttf", font_size = 18 },
        { type = "font", id = "montserrat", file = "./assets/fonts/montserrat.bold.ttf", font_size = 20 }
    },

    ----------------------------------------------------
    --              MAP CONFIG for game               --
    ----------------------------------------------------
    tilemap = {
        mapFile = "./assets/tilemaps/map_test.map",
        textureID = "map",
        tileSize = 32,
        tileScale = 2.0,
        tileCols = 40,
        tileRows = 40,
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
                    up = { x = 0, y = -90 },
                    right = { x = 90, y = 0 },
                    down = { x = 0, y = 90 },
                    left = { x = -90, y = 0 }
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
                    health = 100
                },

                camera_follow = {
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
                    health = 100
                },

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        }
    }
}