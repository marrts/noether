#include <noether_gui/widgets/tpp_widget.h>

#include <plugin_loader/plugin_loader.h>
#include <QApplication>
#include <signal.h>

void handleSignal(int /*sig*/) { QApplication::instance()->quit(); }

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  signal(SIGINT, handleSignal);
  signal(SIGTERM, handleSignal);

  plugin_loader::PluginLoader loader;
  loader.search_paths.insert(PLUGIN_DIR);
  loader.search_libraries.insert(PLUGINS);

  noether::TPPWidget w(std::move(loader));
  w.show();

  return app.exec();
}
