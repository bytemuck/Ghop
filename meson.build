project('ghop', 'c', version : '0.0.0', default_options : ['c_std=c99'])

subdir('modules/ghop_ecs')

executable('sandbox', 'sandbox/main.c', link_with : ghop_ecs, include_directories : ghop_includes)