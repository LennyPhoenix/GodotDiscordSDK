extends PanelContainer


onready var status_line_edit: = $VBoxContainer/Status/LineEdit
onready var activity_info: = $VBoxContainer/Activity

var presence: Discord.Presence setget set_presence


func set_presence(new_presence: Discord.Presence) -> void:
	if new_presence:
		status_line_edit.text = DiscordManager.enum_to_string(
			Discord.Status,
			new_presence.status
		)
		activity_info.activity = new_presence.activity
