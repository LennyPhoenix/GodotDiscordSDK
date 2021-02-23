extends PanelContainer


onready var activity_data: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Activity
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit


func _on_button_down() -> void:
	var activity: Discord.Activity = activity_data.get_activity()

	DiscordManager.activities.update_activity(activity)
	var result: int = yield(DiscordManager.activities, "update_activity_callback")

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
