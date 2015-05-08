pkgplugindir=$(libdir)/mysql/plugin
pkgplugin_LTLIBRARIES= smiles.la
smiles_la_SOURCES = smiles.cc fragment.cc
smiles_la_CPPFLAGS= -DMYSQL_DYNAMIC_PLUGIN $(CPPFLAGS)
smiles_la_LDFLAGS= -module -rpath $(pkgplugindir) $(LDFLAGS)
