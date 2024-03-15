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
        { type = "font", id = "montserrat", file = "./assets/fonts/montserrat.bold.ttf", font_size = 20 },


        { type = "music", id = "soundtrack", file = "./assets/sounds/soundtrack.wav" },
        { type = "sound", id = "meow", file = "./assets/sounds/meow.wav" }
    },




    ----------------------------------------------------
    --              MAP CONFIG for game               --
    ----------------------------------------------------s
    tilemap = {
        mapFilePath = "./assets/tilemaps/Map1Test.map",
        textureID = "tilemap-texture",
        tileSize = 32,
        tileScale = 2.0,
        tileCols = 35,
        tileRows = 40,
        --tileset
        tilePerRow = 10
    },



    ----------------------------------------------------
    --              sound CONFIG for game             --
    ----------------------------------------------------
    musics = {
        musicFilePath = "./assets/sounds/soundtrack.wav",
        assetID = "soundtrack",
        volume = 5,
        loop = -1
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
                    position = { x = 180, y = 300 },
                    scale = { x = 3.0, y = 3.0 },
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

--                boxcollider = {
--                    width = 22,
--                    height = 20,
--                    offset = { x = 16.0, y = 24.0 }
--                },

                health = {
                    healthPercent = 100
                },

                camera = {
                    follow = true
                },

                sfx = {
                    sfxID = "meow",
                    volume = 100,
                    loop = 0,

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









        --TREE A layer 2
        -- x,y -> 64,192 (1280,192 -> 1216,-30)
        --top
        --1
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1216, y = -30 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        --2
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 65, y = 538 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        --3
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 704, y = 406 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        --4
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 892, y = 450 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1025, y = 511 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1281, y = 511 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1473, y = 575 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 896, y = 704 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },

        --middle
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1792, y = 1088 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 640, y = 1192 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1022, y = 1215 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1664, y = 1216 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1792, y = 1277 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 833, y = 1728 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },

        --bottom
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 896, y = 2338 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },










        --tree a
        --layer 2
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 320, y = 352 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 640, y = 487 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1409, y = 381 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1984, y = -28 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 2110, y = 424 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 2113, y = 677 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 2047, y = 1038 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 320, y = 579 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = -2, y = 896 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 63, y = 1538 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 576, y = 1234 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1087, y = 1279 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 2113, y = 1278 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 767, y = 1793 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 896, y = 1780 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1213, y = 1662 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1408, y = 1858 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 2109, y = 1858 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1982, y = 2172 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1663, y = 2305 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 1151, y = 2047 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },
        {
            group = "treeA",
            components = {
                transform = {
                    position = { x = 513, y = 2302 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeA",
                    width = 64,
                    height = 96,
                    zIndex = 2
                },

                boxcollider = {
                    width = 64,
                    height = 96
                }

            }
        },













        --tree b
        --layer 3
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1410, y = 641 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1091, y = 640 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 388, y = 705 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 833, y = 1217 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1538, y = 1216 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 2116, y = 1535 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 2158, y = 1984 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1340, y = 1922 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1281, y = 2267 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 834, y = 1922 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = -23, y = 1345 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 451, y = 2360 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 3
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },



















        --tree b 
        --layer 2
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1701, y = -129 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 2109, y = 33 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 484, y = 510 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1124, y = 365 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1955, y = 1123 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 37, y = 673 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = -28, y = 1758 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 1059, y = 1819 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },
        {
            group = "treeB",
            components = {
                transform = {
                    position = { x = 2087, y = 2263 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeB",
                    width = 61,
                    height = 95,
                    zIndex = 2
                },

                boxcollider = {
                    width = 61,
                    height = 95
                }

            }
        },









        --tree c
        --layer 3
        {
            group = "treeC",
            components = {
                transform = {
                    position = { x = 1454, y = -229 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeC",
                    width = 80,
                    height = 128,
                    zIndex = 3
                },

                boxcollider = {
                    width = 80,
                    height = 128
                }

            }
        },
        {
            group = "treeC",
            components = {
                transform = {
                    position = { x = 736, y = 539 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeC",
                    width = 80,
                    height = 128,
                    zIndex = 3
                },

                boxcollider = {
                    width = 80,
                    height = 128
                }

            }
        },
        {
            group = "treeC",
            components = {
                transform = {
                    position = { x = 241, y = 1688 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeC",
                    width = 80,
                    height = 128,
                    zIndex = 3
                },

                boxcollider = {
                    width = 80,
                    height = 128
                }

            }
        },
        {
            group = "treeC",
            components = {
                transform = {
                    position = { x = 627, y = 1755 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "treeC",
                    width = 80,
                    height = 128,
                    zIndex = 3
                },

                boxcollider = {
                    width = 80,
                    height = 128
                }

            }
        }




    }
} 