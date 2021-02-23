extends PanelContainer


onready var id_line_edit: = $VBoxContainer/ID/LineEdit
onready var party_size: = $VBoxContainer/Size

var party: Discord.ActivityParty setget set_party


func set_party(new_party: Discord.ActivityParty) -> void:
	if new_party:
		id_line_edit.text = new_party.id
		party_size.party_size = new_party.size
