``` cpp

Config config;

// 加载
config.load("config/game.json");

// 读取（支持嵌套！）
float speed = config.get<float>("player.speed");
int hp = config.get<int>("player.hp");
std::string path = config.get<std::string>("textures.player");

// 写入（支持嵌套！）
config.set<float>("camera.zoom", 1.5f);
config.set<bool>("game.debug", true);

// 保存
config.save("config/save.json");
```