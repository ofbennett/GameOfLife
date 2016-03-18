#ifndef WORLD_H_
#define WORLD_H_


class World {
public:
  World();
  void Populate();
  void Record() const;
  void Update();
  int Day() const;

private:
  int day;
};

#endif /* WORLD_H_ */
