#include <milka/milka.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
  milka::Context context = milka::Context();
  
  milka::WindowDescriptor* wdesc = context.GetWindowDescriptor();
  
  wdesc->title = "Milkyy";
  wdesc->width = 800;
  wdesc->height = 600;

  milka::RendererDescriptor* rdesc = context.GetRendererDescriptor();
  
  rdesc->api = milka::RendererAPI::DirectX9;
  rdesc->vsync = true;

  milka::Result res = context.Start();
   
  if (res.res != milka::Result::SUCCESS)
  {
    std::cout << "Error: " << res.error_str << '\n';
    return res.ret;
  }
  
  milka::VertexBuffer buffer(3);
  buffer[0] = {400, 150, {255, 0, 0}};
  buffer[1] = {600, 450, {0, 255, 0}};
  buffer[2] = {200, 450, {0, 0, 255}};

  milka::VertexBuffer wannabequad(5);
  wannabequad[0] = {100, 100, {255, 255, 255}};
  wannabequad[1] = {110, 100, {255, 255, 255}};
  wannabequad[2] = {100, 110, {255, 255, 255}};
  wannabequad[3] = {110, 110, {255, 255, 255}};
  wannabequad[4] = {105, 115, {255, 255, 255}};
  
  bool quit = false;
  while (!quit)
  {
    milka::Event* e = context.GetEvent();
    milka::RendererInternal* renderer = context.GetRenderer()->GetInternal();

    e->update_events();

    if (e->has_key(milka::KeyCode::ESC) || e->contains(milka::EventType::QUIT))
      quit = true;
    
    renderer->setBackgroundColor(30, 30, 30);
    renderer->begin();
    
    renderer->drawVertexBuffer(buffer);
    renderer->drawVertexBuffer(wannabequad);

    renderer->end();
  }

  return 0;
}
