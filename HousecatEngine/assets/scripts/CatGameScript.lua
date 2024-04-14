-----------------------------------------------
--            LUA SCRIPT TEST                --
-----------------------------------------------

--local
local map_

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
        { type = "sound", id = "meow", file = "./assets/sounds/meow.wav" },
        { type = "sound", id = "damage", file = "./assets/sounds/damage.wav" },
        { type = "sound", id = "death", file = "./assets/sounds/death.wav" }
    },




    ----------------------------------------------------
    --              MAP CONFIG for game               --
    ----------------------------------------------------s
    tilemap = {
        mapFilePath = "./assets/tilemaps/HauntedForest.map",
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
                    position = { x = 20, y = 230 },
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

                boxcollider = {
                    width = 22, 
                    height = 20,
                    offset = { x = 16.0, y = 24.0 }
                },

                health = {
                    healthPercent = 100,
                    lowHealth = { 255, 0, 0 },
					mediumHealth = { 255, 255, 0 },
					highHealth = { 0, 255, 0 },
					healthBarWidth = 35,
					healthBarHeight = 5,
					horizontalOffset = 65,
					verticalOffset = 0
                },

                camera = {
                    follow = true
                },

                sfx = {
                    sfxID = "meow",
                    volume = 100,
                    loop = 0,
                    isPlaying = false,
                    delay = 4
                }
            }
        },






        --NPC
        --LEFT
        {
            group = "npc",
            components = {
                transform = {
                    position = { x = 5, y = 2480 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "npc",
                    width = 32,
                    height = 32,
                    zIndex = 2,
                    fixed = false,
                    srcRectX = 32,
                    srcRectY = 32
                }
            }
        },
        --MIDDLE
        {
            group = "npc",
            components = {
                transform = {
                    position = { x = 184, y = 2477 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "npc",
                    width = 32,
                    height = 32,
                    zIndex = 2,
                    fixed = false,
                    srcRectX = 0,
                    srcRectY = 0,
                }
            }
        },
        --RIGHT
        {
            group = "npc",
            components = {
                transform = {
                    position = { x = 100, y = 2477 },
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
                }
            }
        },







        --ENEMY STATIC
       {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 577, y = 402 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 776, y = 200 },
                    scale = { x = 2.5, y = 2.5 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

       {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1647, y = 449 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1728, y = 828 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1916, y = 1026 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1217, y = 1066 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 640, y = 1174 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 284, y = 1469 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 768, y = 1598 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1594, y = 1537 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1693, y = 2030 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1729, y = 2235 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1271, y = 2129 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 4,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1120, y = 2115 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 722, y = 2379 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 261, y = 2312 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "slime",
                    width = 44,
                    height = 30,
                    zIndex = 1,
                    flip = 1
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                }
            }
        },

        








        --ENEMY MOVING HORIZONTAL
        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1800, y = 353 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1700  or current_position_x > 2050 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1800, y = 645 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1795  or current_position_x > 2174 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1100, y = 910 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 100.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1050  or current_position_x > 1480 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 900, y = 1230 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 885  or current_position_x > 1555 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 300, y = 1044 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 213  or current_position_x > 991 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 40, y = 1350 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 100.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 35  or current_position_x > 400 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 640, y = 1475 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 640  or current_position_x > 1015 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1000, y = 1725 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = -200.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 577  or current_position_x > 1245 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1500, y = 1726 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 100.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1473  or current_position_x > 2069 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1700, y = 1920 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 50.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1640  or current_position_x > 2070 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1800, y = 2114 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = -80.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 1664  or current_position_x > 2029 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 400, y = 2200 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = -200.0, y = 0.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_x < 80  or current_position_x > 800 then
                            set_velocity(entity, current_velocity_x * -1, 0 );
                            if current_velocity_x * -1 > 0 then
                                --flip on horizontal axis
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, current_velocity_x, 0);
                            if current_velocity_x > 0 then
                                --flip to right
                                set_sprite_flip(entity, 1);
                            else
                                --no flip
                                set_sprite_flip(entity, 0);
                            end
                        end
                    end
                }
                
            }
        },





        









        --ENEMY MOVING VERTICAL
        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1051, y = 159 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 150.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 160  or current_position_y > 495 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1380, y = 498 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = -50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 140  or current_position_y > 498 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1569, y = 845 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 845  or current_position_y > 1225 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 500, y = 900 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 200.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 900  or current_position_y > 1300 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 500, y = 1369 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 100.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 1369  or current_position_y > 1720 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 161, y = 1107 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 1107  or current_position_y > 1637 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1278, y = 1771 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = -50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 1420  or current_position_y > 1775 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1891, y = 1505 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 200.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 1505  or current_position_y > 2350 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                                --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end

                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1567, y = 2143 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 2140  or current_position_y > 2430 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1413, y = 2200 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 80.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 2140  or current_position_y > 2428 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 1090, y = 2156 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 2130  or current_position_y > 2430 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 900, y = 2200 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 200.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 2120  or current_position_y > 2420 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },

        {
            group = "enemy",
            components = {
                transform = {
                    position = { x = 495, y = 2096 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0,
                },

                sprite = {
                    textureID = "ghost",
                    width = 32,
                    height = 32,
                    zIndex = 2
                },

                rigidbody = {
                    velocity = { x = 0.0, y = 50.0 }
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

                damageArea = {
                    isFriendly = false,
	                hitDamage = 20,
	                damageDelay = 1.0
                },

                script = {
                [0] =
                    function(entity, delta_time, ellapsed_time)
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        --define the movement area
                        if current_position_y < 2096  or current_position_y > 2460 then
                            set_velocity(entity, 0, current_velocity_y * -1);
                            --flip sprite vert
                            if current_velocity_y > 0 then
                                set_sprite_flip(entity, 1);
                            else
                                set_sprite_flip(entity, 0);
                            end
                        else
                            set_velocity(entity, 0, current_velocity_y);
                        end
                    end
                }
                
            }
        },




        --WIN AREA
        {
            group = "win",
            components = {
                transform = {
                    position = { x = 0, y = 2431 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0,
                },

                boxcollider = {
                    width = 256,
                    height = 2431,
                    offset = { x = 0.0, y = 0.0 }
                },

                winning = {}
            }
        },
         --WIN TEXT
        {
            tag = "winMessage",
            components = {
                text = {
                    fontID = "roboto",
                    position = {  x = 125, y = 2170 },
                    isFixed = false,
                    isVisible = false,
                    text = "You Found Your Colony!",
                    color = { r = 255, g = 255, b = 255, a = 255 }
                },

                sfx = {
                    sfxID = "meow",
                    volume = 100,
                    loop = 0,
                    isPlaying = false,
                    delay = 1
                }
            }
         },

         --DEATH TEXT
         {
            tag = "death",
            components = {
                text = {
                    fontID = "montserrat",
                    position = {  x = 0, y = 0 },
                    isFixed = true,
                    isVisible = false,
                    text = "You Died!",
                    color = { r = 255, g = 0, b = 0, a = 255 }
                },

                sfx = {
                    sfxID = "death",
                    volume = 100,
                    loop = 0,
                    isPlaying = false,
                    delay = 1
                },

                --TODO
                boxcollider = {
                    width = 0,
                    height = 0,
                    offset = { x = 0.0, y = 0.0 }
                },
             },
         },




        --TEXT
        {
            group = "message",
            components = {
                text = {
                    fontID = "roboto",
                    position = {  x = 12, y = 144 },
                    isFixed = false,
                    isVisible = true,
                    text = "Find your colony!",
                    color = { r = 0, g = 0, b = 0, a = 255 }
                }
            }
         },

         {
            group = "message",
            components = {
                text = {
                    fontID = "roboto",
                    position = {  x = 758, y = 319 },
                    isFixed = false,
                    isVisible = true,
                    text = "Avoid the monsters!",
                    color = { r = 0, g = 0, b = 0, a = 255 }
                }
             }
         },




         






        --TREE A layer 2
        -- x,y -> 64,192 (1280,192 -> 1216,-30)
        --top
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


-- global var
--for map
map_width = Level.tilemap.tileCols * Level.tilemap.tileSize * Level.tilemap.tileScale
map_height = Level.tilemap.tileRows * Level.tilemap.tileSize * Level.tilemap.tileScale