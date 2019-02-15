project('snake','cpp',
    version : '2.1'
)

snake_inc = include_directories('include')
snake_src = files(
    'src/main.cpp',
    'src/objects.cpp',
    'src/snake.cpp',
    'src/snake_draw.cpp',
    'src/WindowHandler.cpp',
)

gtkmm_dep = dependency('gtkmm-3.0')

executable('snake', snake_src,
    dependencies : [gtkmm_dep],
    include_directories : snake_inc,
    install : true
)