ghop_includes = include_directories('include')
ghop_sources = ['src/ecs.c']
ghop_ecs = static_library('ghop_ecs', ghop_sources, include_directories : ghop_includes)

test_add_components = executable('test_add_components', ['test/test_AddComponents.c'], include_directories : ghop_includes, link_with: ghop_ecs)
test('test_add_components', test_add_components)