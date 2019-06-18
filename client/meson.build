project('r2p_client', 'cpp', default_options: ['warning_level=3'])

qt5_module = import('qt5')
qt5_deps = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'Network'])

qt5_processed = qt5_module.preprocess(
  moc_headers: ['client.h', 'connectWindow.h'],
  ui_files   : ['client.ui', 'connectWindow.ui'],
  qresources : 'resources.qrc',
)

r2p_inc = include_directories('../r2p')
r2p_dep = meson.get_compiler('cpp').find_library('r2p', dirs: join_paths([meson.source_root(), '../r2p']))

exe = executable('client',
	sources: ['main.cpp', 'client.cpp', 'connectWindow.cpp', qt5_processed],
	include_directories: r2p_inc,
	dependencies: [qt5_deps, r2p_dep])
