extends PanelContainer


onready var user_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/UserId
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_button_down() -> void:
	var user_id: String = user_id_line_edit.text

	DiscordManager.activities.accept_invite(int(user_id))
	var result: int = yield(DiscordManager.activities, "accept_invite_callback")

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
