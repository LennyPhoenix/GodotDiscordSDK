extends PanelContainer


onready var join_line_edit: = $VBoxContainer/Join/LineEdit
onready var spectate_line_edit: = $VBoxContainer/Spectate/LineEdit

var secrets: Discord.ActivitySecrets setget set_secrets


func set_secrets(new_secrets: Discord.ActivitySecrets) -> void:
	if new_secrets:
		join_line_edit.text = new_secrets.join
		spectate_line_edit.text = new_secrets.spectate
