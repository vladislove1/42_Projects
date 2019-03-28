#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "gui.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <vector>
#include <iostream>
#include <cmath>

t_vec3 ToVec3(cl_float3 vec) {
	return vec3_init(vec.x, vec.y, vec.z);
}

cl_float3 ToCL(t_vec3 vec) {
	return {{vec.x, vec.y, vec.z}};
}

bool init_gui(t_sdl *sdl) {
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
   
    sdl->gl_context = SDL_GL_CreateContext(sdl->window);

	ImGui_ImplSdlGL3_Init(sdl->window);
	ImGui::StyleColorsClassic();

	sdl->gl_context = SDL_GL_CreateContext(sdl->window);
	if (sdl->gl_context == nullptr) {
		std::cout << "Unable to create OpenGL context." << std::endl;
		return false;
	} else {
		std::cout << "OpenGL context created succesfully." << std::endl;
	}

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) {
		printf("Error initializing GLEW: %s.\n", glewGetErrorString(err));
		return false;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	return true;
}

std::vector<std::string> g_objectTypeStrings = {
	"Sphere",
	"Plane",
	"Cone",
	"Cylinder",
	"Disk",
	"Mobius",
	"Torus",
	"Triangle",
	"Parabola",
	"Ellipsoid",
};

std::vector<std::string> g_objectProcedureStrings = {
	"Default",
	"Checkerboard",
	"Grid",
	"Brick",
	"Perlin noise",
	"Normal disruption",
	"Texture_1",
	"Texture_2",
	"Texture_3",
};

void create_default_primitives(t_primitive *primitive, int i)
{
	switch (i) {
		case SPHERE: {
			primitive->s.r2 = 1.0f;
			break;
		}
		case PLANE: {
			primitive->pl.normal.y = 1.0f;
			break;
		}
		case CONE: {
			primitive->cone.axis.y = 1.0f;
			primitive->cone.angle = M_PI / 6.0f;
			primitive->cone.h = 5.0f;
			break;
		}
		default:
			break;
	}
}

void add_object(t_app *app, int i) {
	s_obj *obj = (s_obj*)ft_memalloc(sizeof(s_obj));

	obj->color = {{1.0f, 1.0f, 1.0f, 1.0f}};
	obj->scale = 1.0f;
	obj->horiz_shift = 0.0f;
	obj->vertic_shift = 0.0f;
	obj->type = i;
    create_default_primitives(&obj->primitive, i);
	switch (i) {
		case CYLINDER: {
			obj->primitive.cyl.axis.y = 1.0f;
			obj->primitive.cyl.r = 1.0f;
            obj->primitive.cyl.h = 5.0f;
			break;
		}
		case DISK: {
			obj->primitive.disk.normal.z = 1.0f;
			obj->primitive.disk.r = 1.0f;
			break;
		}
		case MOBIUS: {
			obj->primitive.mobius.a = 0.5f;
			obj->primitive.mobius.axis_y.y = 1.0f;
			obj->primitive.mobius.axis_x.x = 1.0f;
			obj->primitive.mobius.r = 2.0f;
			break;
		}
		case TORUS: {
			obj->primitive.torus.axis.y = 1.0f;
			obj->primitive.torus.r_1 = 1.0f;
			obj->primitive.torus.r_2 = 2.0f;
			break;
		}
		case PARABOLA: {
			obj->primitive.parab.a = 1.0f;
			obj->primitive.parab.axis.y = 1.0f;
			break;
		}
		case ELLIPSOID: {
			obj->primitive.ellips.a = 1.0f;
			obj->primitive.ellips.r = 2.0f;
			obj->primitive.ellips.axis.y = 1.0f;
			break;
		}
		case TRIANGLE: {
			obj->primitive.triangle.point_b.x = 1.0f;
			obj->primitive.triangle.point_b.y = -1.0f;
			obj->primitive.triangle.point_c.x = -1.0f;
			obj->primitive.triangle.point_c.y = -1.0f;
			break;
		}
		default:
			break;
	}
	ft_lst_push_front(&app->scene->primitives, obj);
	app->scene->num_objects++;
	update_object_buffers(app);
}

void add_light(t_app *app, int i)
{
	s_light *light = (s_light*)ft_memalloc(sizeof(s_light));
	light->intensity = 0.5f;
	light->type = i;
	create_default_primitives(&light->primitive, i);
	ft_lst_push_front(&app->scene->lights, light);
	app->scene->num_lights++;
	update_lights_buffers(app);
}

void render_objects_gui(t_app *app)
{
	s_list *head = app->scene->primitives;
	int i = 1;
	bool was_updated = false;
	auto update_vec3 = [&was_updated](cl_float4& vec3) -> void {
		was_updated = true;
		if (!vec3.x && !vec3.y && !vec3.z)
			vec3.x += 1.0f;
		vec3 = ToCL(vec3_normalize(ToVec3(vec3)));
	};

	int objectToDelete = -1;

	if (ImGui::CollapsingHeader("Objects")) {
		while (head) {
			ImGui::Indent();
			s_obj *obj = reinterpret_cast<s_obj*>(head->content);
			if (ImGui::TreeNode((g_objectTypeStrings[obj->type] + " " + std::to_string(i)).c_str())) {
				if (ImGui::TreeNode(("Transform " + std::to_string(i)).c_str())) {
					switch (obj->type) {
						case SPHERE: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.s.position, 0.05f))
								was_updated = true;

							float r = std::sqrtf(obj->primitive.s.r2);
							if (ImGui::DragFloat(("Radius " + std::to_string(i)).c_str(), &r, 0.05f, 0.0f, std::numeric_limits<float>::max())) {
								was_updated = true;
								obj->primitive.s.r2 = r * r;
							}
							break;
						}
						case CONE: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.cone.position, 0.05f))
								was_updated = true;
							if (ImGui::SliderAngle(("Angle " + std::to_string(i)).c_str(), &obj->primitive.cone.angle, 0.0f, 60.0f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&obj->primitive.cone.axis, 0.05f))
								update_vec3(obj->primitive.cone.axis);
							if (ImGui::DragFloat(("Height " + std::to_string(i)).c_str(), &obj->primitive.cone.h, 0.05f, 0.0f, 1e20f))
								was_updated = true;
							break;
						}
						case CYLINDER: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.cyl.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&obj->primitive.cyl.axis, 0.05f)) 
								update_vec3(obj->primitive.cyl.axis);
							if (ImGui::DragFloat(("Radius " + std::to_string(i)).c_str(), &obj->primitive.cyl.r, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							if (ImGui::DragFloat(("Height " + std::to_string(i)).c_str(), &obj->primitive.cyl.h, 0.05f, 0.01f, 1e20f))
								was_updated = true;
							break;
						}
						case PLANE: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.pl.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Normal " + std::to_string(i)).c_str(), (float*)&obj->primitive.pl.normal, 0.05f))
								update_vec3(obj->primitive.pl.normal);
							break;
						}
						case DISK: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.disk.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Normal " + std::to_string(i)).c_str(), (float*)&obj->primitive.disk.normal, 0.05f))
								update_vec3(obj->primitive.disk.normal);
							if (ImGui::DragFloat(("Radius " + std::to_string(i)).c_str(), &obj->primitive.disk.r, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							break;
						}
						case MOBIUS: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.mobius.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis X " + std::to_string(i)).c_str(), (float*)&obj->primitive.mobius.axis_x, 0.05f))
								update_vec3(obj->primitive.mobius.axis_x);
							if (ImGui::DragFloat3(("Axis Y " + std::to_string(i)).c_str(), (float*)&obj->primitive.mobius.axis_y, 0.05f))
								update_vec3(obj->primitive.mobius.axis_y);
							if (ImGui::DragFloat(("Radius " + std::to_string(i)).c_str(), &obj->primitive.mobius.r, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							if (ImGui::DragFloat(("Width " + std::to_string(i)).c_str(), &obj->primitive.mobius.a, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							break;
						}
						case ELLIPSOID: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.ellips.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&obj->primitive.ellips.axis, 0.05f))
								update_vec3(obj->primitive.ellips.axis);
							if (ImGui::DragFloat(("A " + std::to_string(i)).c_str(), &obj->primitive.ellips.a, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							if (ImGui::DragFloat(("B " + std::to_string(i)).c_str(), &obj->primitive.ellips.r, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							break;
						}
						case TRIANGLE: {
							if (ImGui::DragFloat3(("Point 1 " + std::to_string(i)).c_str(), (float*)&obj->primitive.triangle.point_a, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Point 2 " + std::to_string(i)).c_str(), (float*)&obj->primitive.triangle.point_b, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Point 3 " + std::to_string(i)).c_str(), (float*)&obj->primitive.triangle.point_c, 0.05f))
								was_updated = true;
							break;
						}
						case TORUS: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.torus.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&obj->primitive.torus.axis, 0.05f))
								update_vec3(obj->primitive.ellips.axis);
							if (ImGui::DragFloat(("Minor radius " + std::to_string(i)).c_str(), &obj->primitive.torus.r_1, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							if (ImGui::DragFloat(("Major radius " + std::to_string(i)).c_str(), &obj->primitive.torus.r_2, 0.05f, obj->primitive.torus.r_1, std::numeric_limits<float>::max()))
								was_updated = true;
							break;
						}
						case PARABOLA: {
							if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&obj->primitive.parab.position, 0.05f))
								was_updated = true;
							if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&obj->primitive.parab.axis, 0.05f))
								update_vec3(obj->primitive.ellips.axis);
							if (ImGui::DragFloat(("A " + std::to_string(i)).c_str(), &obj->primitive.parab.a, 0.05f, 0.0f, std::numeric_limits<float>::max()))
								was_updated = true;
							break;
						}
						default:
							break;
					}
					ImGui::TreePop();
				}


				if (ImGui::TreeNode(("Material " + std::to_string(i)).c_str())) {
					if (ImGui::SliderFloat(("Ambient " + std::to_string(i)).c_str(), &obj->ambient, 0.0f, 1.0f))
						was_updated = true;
					if (ImGui::SliderFloat(("Reflection " + std::to_string(i)).c_str(), &obj->reflect, 0.0f, 1.0f))
						was_updated = true;
					if (ImGui::SliderFloat(("Refraction " + std::to_string(i)).c_str(), &obj->refract, 0.0f, 1.0f))
						was_updated = true;
					if (ImGui::SliderInt(("Specular " + std::to_string(i)).c_str(), &obj->specular, 0, 100))
						was_updated = true;
					if (ImGui::SliderFloat(("Transparent " + std::to_string(i)).c_str(), &obj->transparency, 0.0f, 1.0f))
						was_updated = true;
					if (ImGui::ColorEdit3(("Color " + std::to_string(i)).c_str(), (float*)&obj->color))
						was_updated = true;
					if (obj->type <= CYLINDER) {
						if (ImGui::ColorEdit3(("Color 2 " + std::to_string(i)).c_str(), (float*)&obj->color2))
							was_updated = true;
						if (ImGui::SliderFloat(("Scale " + std::to_string(i)).c_str(), &obj->scale, 1.0f, 10.0f))
							was_updated = true;
						if (ImGui::SliderFloat(("Horizontal shift " + std::to_string(i)).c_str(), &obj->horiz_shift, -20.0f, 20.0f))
							was_updated = true;
						if (ImGui::SliderFloat(("Vertical shift " + std::to_string(i)).c_str(), &obj->vertic_shift, -20.0f, 20.0f))
							was_updated = true;
						if (ImGui::Button("Object's procedure")) {
							ImGui::OpenPopup("procedure");
						}
					}
					if (ImGui::BeginPopup("procedure")) {
						ImGui::Text("Object's procedure");
						ImGui::Separator();
						for (int j = 0; j < PROCEDURE_NUM; ++j) {
							if (ImGui::Selectable(g_objectProcedureStrings[j].c_str())) {
								obj->proced = j;
								was_updated = true;
							}
						}
						ImGui::EndPopup();
					}

					ImGui::TreePop();
				}

				if (ImGui::Button(("Remove object " + std::to_string(i)).c_str())) {
					objectToDelete = i - 1;
				}

				ImGui::TreePop();
			}
			ImGui::Unindent();
			i++;
			head = head->next;
		}
		if (was_updated)
			update_object_buffers(app);
		if (objectToDelete != -1)
			remove_object(app, objectToDelete);
	}
	if (ImGui::CollapsingHeader("Lights")) {
		ImGui::Indent();
		s_list *lightHead = app->scene->lights;
		i = 1;
		int lightToDelete = -1;
		was_updated = false;
		while (i <= app->scene->num_lights) {
			s_light *light = reinterpret_cast<s_light*>(lightHead->content);
			if (ImGui::TreeNode(("Light " + std::to_string(i)).c_str())) {
				if (ImGui::DragFloat3(("Position " + std::to_string(i)).c_str(), (float*)&light->primitive.position))
					was_updated = true;
				if (ImGui::SliderFloat(("Intensity " + std::to_string(i)).c_str(), &light->intensity, 0.0f, 1.0f))
					was_updated = true;
				switch (light->type) {
					case PLANE: {
						if (ImGui::DragFloat3(("Normal " + std::to_string(i)).c_str(), (float*)&light->primitive.pl.normal, 0.05f))
							update_vec3(light->primitive.pl.normal);
						break;
					}
					case CONE: {
						if (ImGui::SliderAngle(("Angle " + std::to_string(i)).c_str(), &light->primitive.cone.angle, 0.0f, 60.0f))
							was_updated = true;
						if (ImGui::DragFloat3(("Axis " + std::to_string(i)).c_str(), (float*)&light->primitive.cone.axis, 0.05f))
							update_vec3(light->primitive.cone.axis);
						break;
					}
				}
				if (ImGui::Button("Light's type"))
					ImGui::OpenPopup("types");
				if (ImGui::BeginPopup("types")) {
					ImGui::Text("Light's type");
					ImGui::Separator();
					for (int j = 0; j <= CONE; ++j) {
						if (ImGui::Selectable(g_objectTypeStrings[j].c_str())) {
							light->type = j;
							was_updated = true;
						}
					}
					ImGui::EndPopup();
				}
				if (ImGui::Button(("Remove light " + std::to_string(i)).c_str()))
					lightToDelete = i - 1;
				ImGui::TreePop();
			}

			i++;
			lightHead = lightHead->next;
		}
		ImGui::Unindent();
		if (was_updated)
			update_lights_buffers(app);
		if (lightToDelete != -1)
			remove_light(app, lightToDelete);
	}
}

void render_gui(t_app *app) {
	assert(g_objectTypeStrings.size() == PRIMITIVE_TYPES_AMOUNT);

	ImGui_ImplSdlGL3_NewFrame(app->sdl.width, app->sdl.height);
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);

	ImGui::SetNextWindowSizeConstraints(ImVec2(250, 300), ImVec2(app->sdl.width, app->sdl.height));
	ImGui::Begin("Configuration", NULL, ImGuiWindowFlags_AlwaysAutoResize);

	render_objects_gui(app);

	if (ImGui::Button("Add object")) {
		ImGui::OpenPopup("Object_types");
	}
	if (ImGui::BeginPopup("Object_types")) {
		ImGui::Text("Object types");
		ImGui::Separator();
		for (int i = 0; i < PRIMITIVE_TYPES_AMOUNT; ++i) {
			if (ImGui::Selectable(g_objectTypeStrings[i].c_str())) {
				add_object(app, i);
			}
		}
		ImGui::EndPopup();
	}

	if (ImGui::Button("Add light")) {
		ImGui::OpenPopup("Light_types");
	}
	if (ImGui::BeginPopup("Light_types")) {
		ImGui::Text("Add light");
		ImGui::Separator();
		for (int i = 0; i <= CONE; ++i) {
			if (ImGui::Selectable(g_objectTypeStrings[i].c_str())) {
				add_light(app, i);
			}
		}
		ImGui::EndPopup();
	}

	ImGui::End();
	ImGui::Render();
}

void process_gui_event(SDL_Event* event){
	auto& io = ImGui::GetIO();
	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
		io.MouseDown[0] = true;
	} else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) {
		io.MouseDown[0] = false;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_RIGHT) {
		io.MouseDown[1] = true;
	} else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_RIGHT) {
		io.MouseDown[1] = false;
	}

	if (event->type == SDL_MOUSEMOTION && event->button.button == SDL_BUTTON_LEFT) {
		io.MousePos = ImVec2((float)event->motion.x, (float)event->motion.y);
	}

	if (event->type == SDL_MOUSEMOTION) {
		io.MousePos = ImVec2((float)event->motion.x, (float)event->motion.y);
	}
	ImGui_ImplSdlGL3_ProcessEvent(event);
}
