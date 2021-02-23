extends PanelContainer


onready var user_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/UserId
onready var type_options: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Type
onready var content_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Content
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _ready() -> void:
	for item in Discord.ActivityActionType.keys():
		type_options.add_item(item, Discord.ActivityActionType[item])


func _on_button_down() -> void:
	var user_id: String = user_id_line_edit.text
	var type: int = type_options.get_selected_id()
	var content: String = content_line_edit.text

	DiscordManager.activities.send_invite(int(user_id), type, content)
	var result: int = yield(DiscordManager.activities, "send_invite_callback")

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
