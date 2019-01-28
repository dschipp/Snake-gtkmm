project('snake', 'cpp'
  version : '0.1'
)

snake_inc = include_directories('include')
snake_src = files(
  'src/FruitObj.cpp',
  'src/main.cpp',
  'src/Snake.cpp',
  'src/SnakeObj.cpp',
  'src/Spielfeld.cpp',
  'src/WindowHandler.cpp'
)

gtkmm_dep = dependency('gtkmm-3.0')

executable('snake', snake_src,
  dependencies : [gtkmm_dep],
  include_directories : snake_inc,
  install : true
)
