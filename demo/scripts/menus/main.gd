extends ScrollContainer


signal switch_to(menu)


func _on_users_button_up() -> void:
	emit_signal("switch_to", Main.Menu.USERS)


func _on_images_button_up() -> void:
	emit_signal("switch_to", Main.Menu.IMAGES)
