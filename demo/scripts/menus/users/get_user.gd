extends PanelContainer


onready var id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/LineEdit
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit
onready var user_info: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/User


func _on_fetch_button_down() -> void:
	var id: String = id_line_edit.text

	DiscordManager.users.get_user(int(id))
	var ret: Array = yield(DiscordManager.users, "get_user_callback")
	var result: int = ret[0]
	var user: Discord.User = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
	user_info.user = user
