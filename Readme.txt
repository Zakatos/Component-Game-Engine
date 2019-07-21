The main feature of my engine is mainly the entity component system i am using.
Each entity with this approach is an aggregate of components, it is potentially
more cahce-friendly , it has minmal runtime overhead and good flexibility.
Component types are know at compile and they contain a bitset of their
available components.In addition this engine uses the singleton pattern
to create instances of manager classes which can we can call whenever needed.
The command design pattern is also implemented to easily map keys from 
different input devices and call entity actions.





-Need more work/Future improvements or additions
  -Threading especially in the part of joining.
  -Collision detection and how the physics currently work
  -Adding a scenegraph
  -Post initialization and introduction of a fixed update.
  -Events for communication between unrelated entities. 
  -Const correctness 
