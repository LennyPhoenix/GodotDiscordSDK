extends PanelContainer


onready var user_id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/UserID
onready var reply_option_button: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Reply/OptionButton
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _ready() -> void:
	for item in Discord.ActivityJoinRequestReply.keys():
		reply_option_button.add_item(item, Discord.ActivityJoinRequestReply[item])


func _on_button_down() -> void:
	var user_id: String = user_id_line_edit.text
	var reply: int = reply_option_button.get_selected_id()

	DiscordManager.activities.send_request_reply(int(user_id), reply)
	var result: int = yield(DiscordManager.activities, "send_request_reply_callback")

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
