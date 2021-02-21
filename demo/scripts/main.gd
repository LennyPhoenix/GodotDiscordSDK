extends Control
class_name Main


enum Menu {
	MAIN,
	USERS,
}


onready var back_button: = $MarginContainer/VBoxContainer/Title/BackButton
onready var main_menu: = $MarginContainer/VBoxContainer/Menu/MarginContainer/Main
onready var users_menu: = $MarginContainer/VBoxContainer/Menu/MarginContainer/Users


func _on_main_switch_to(menu: int) -> void:
	match menu:
		Menu.MAIN:
			to_main()
		Menu.USERS:
			to_users()


func _hide_all() -> void:
	back_button.disabled = false
	main_menu.visible = false
	users_menu.visible = false


func to_main() -> void:
	_hide_all()
	back_button.disabled = true
	main_menu.visible = true


func to_users() -> void:
	_hide_all()
	users_menu.visible = true
