TEMPLATE = subdirs

SUBDIRS = \
	r2p \
	client \
	server

client.depends = r2p
server.depends = r2p

# TODO: centralize compile options here
