/// Helpful stuff:
// https://gist.github.com/zester/2402725
// 


#include "pandaFramework.h"
#include "pandaSystem.h"
#include "directionalLight.h"
#include "antialiasAttrib.h"
#include "load_prc_file.h"
#include "loader.h"
#include "texturePool.h"
#include "shaderPool.h"
#include "material.h"
#include "shader.h"
#include "main.h"

#include <iostream>


// Global Stuff
PandaFramework framework;
NodePath camera;
WindowFramework *window;

// Models
NodePath monitorModel;
NodePath screenModel;

// Textures
PNMImage screenImg;
PT(Texture) screenTex;

int main(int argc, char *argv[]) {
  std::cout << "Starting..." << "\n";

  // Open a new window framework
  load_prc_file_data("", "framebuffer-multisample 1");
  load_prc_file_data("", "multisamples 8");

  framework.open_framework(argc, argv);
  framework.set_window_title("Terminal");

  // Set things up
  window = framework.open_window();
  camera = window->get_camera_group(); // Get the camera and store it
  load_models();

  // Light
  PT(DirectionalLight) d_light;
  d_light = new DirectionalLight("my d_light");
  d_light->set_color( LVecBase4f( 0.6, 0.6, 0.6, 1 ) );

  NodePath dlnp = window->get_render().attach_new_node(d_light);
  dlnp.set_hpr(15, -20, 0);  // Facing away from camera

  // Apply Render Settings
  window->get_render().set_light(dlnp);   //affect everything
  window->get_render().set_antialias(AntialiasAttrib::M_multisample);


  // Do the main loop, equal to run() in python
  framework.main_loop();
  framework.close_framework();
  return (0);
}

void load_charmap() {
    
}

void update_image() {
  screenTex->load(screenImg);
}

void load_models() {
  // Monitor
  monitorModel = window->load_model(framework.get_models(), "models/computer/monitor.egg");
  monitorModel.set_pos(0, 3, -.3);
  monitorModel.set_hpr(270, 0, 0);
  monitorModel.reparent_to(window->get_render());


  // Screen
  screenTex = new Texture("screen");
  screenImg = PNMImage (640, 480);
  screenImg.fill(0, 0, 0);
  screenImg.set_xel(5, 5, LVecBase3f(1, 1, 1));
  update_image();

  // Screen Material
  Material *screenMat = new Material;
  screenMat->set_ambient(LColor(1, 1, 1, 1));
  screenMat->set_diffuse(LColor(1, 1, 1, 1));
  screenMat->set_emission(LColor(1, 1, 1, 1));

  screenModel = window->load_model(framework.get_models(), "models/computer/screen.egg");
  screenModel.set_texture_off(1);
  screenModel.set_material(screenMat, 1);
  screenModel.set_texture(screenTex, 1);
  screenModel.set_pos(0, 3, -.3);
  screenModel.set_hpr(270, 0, 0);

  screenModel.reparent_to(window->get_render());
}