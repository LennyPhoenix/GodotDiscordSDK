extends PanelContainer


onready var join_line_edit: = $VBoxContainer/Join
onready var spectate_line_edit: = $VBoxContainer/Spectate


func get_secrets() -> Discord.ActivitySecrets:
	var secrets: = Discord.ActivitySecrets.new()
	secrets.join = join_line_edit.text
	secrets.spectate = spectate_line_edit.text
	return secrets
