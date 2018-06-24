/*  +---------------------------------------------------------------------------+
*  |                                                                           |
*  | Fluicell AB, http://fluicell.com/                                         |
*  | Biopen wizard 2.1                                                         |
*  |                                                                           |
*  | Authors: Mauro Bellone - http://www.maurobellone.com                      |
*  | Released under GNU GPL License.                                           |
*  +---------------------------------------------------------------------------+ */


#include "Lab-on-a-tip.h"

void Labonatip_GUI::dropletSizePlus() {

	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::dropletSizePlus    " << endl;

	// only Pon + percentage
	// V_recirc - percentage
	if (m_pipette_active) {
		bool success = false;
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeDropletSizeBy(m_pr_params->base_ds_increment);
		}
		else {
			success = m_ppc1->setDropletSize(
				m_ds_perc + 
				m_pr_params->base_ds_increment);
		}

		if(!success) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}
		else
		{
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();
			m_pipette_status->pon_set_point = m_ppc1->getPonSetPoint();

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);
			ui->horizontalSlider_p_on->blockSignals(true);
			ui->horizontalSlider_p_on->setValue(m_pipette_status->pon_set_point);
			ui->horizontalSlider_p_on->blockSignals(false);
		}
	}
	if (m_simulationOnly) {

		if (m_ds_perc > MAX_ZONE_SIZE_PERC - 2*m_pr_params->base_ds_increment) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done); 
			return;
		}

		double perc = (m_ds_perc + 
			m_pr_params->base_ds_increment) / 100.0;

		if (ui->horizontalSlider_recirculation->value() == 0) {
			QMessageBox::information(this, m_str_warning,
				" Recirculation zero, " + m_str_operation_cannot_be_done);
			return;
		}
		else {
			double delta = (1.0 - std::pow(perc, (1.0 / 3.0)));
			double value = -m_pr_params->v_recirc_default - m_pr_params->v_recirc_default * delta;

			updateVrecircSetPoint(value);
		}

		if (ui->horizontalSlider_p_on->value() == 0) {
			updatePonSetPoint(3.0);
		}
		else {
			double delta = (1.0 - std::pow(perc, (1.0 / 3.0)));
			double value = m_pr_params->p_on_default - m_pr_params->p_on_default  * delta;

			updatePonSetPoint(value);
		}

		updateFlowControlPercentages();
	}
}

void Labonatip_GUI::dropletSizeMinus() {

	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::dropletSizeMinus    " << endl;

	// only Pon - percentage
	// V_recirc + percentage
	if (m_pipette_active) {
		bool success = false;
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeDropletSizeBy(-m_pr_params->base_ds_increment);
		}
		else {
			success = m_ppc1->setDropletSize( m_ds_perc -
				m_pr_params->base_ds_increment);
		}

		if (!success){
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound); 
		}
		else
		{
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();
			m_pipette_status->pon_set_point = m_ppc1->getPonSetPoint();

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);
			ui->horizontalSlider_p_on->blockSignals(true);
			ui->horizontalSlider_p_on->setValue(m_pipette_status->pon_set_point);
			ui->horizontalSlider_p_on->blockSignals(false);
		}
	}
	if (m_simulationOnly) {
	
		if (m_ds_perc < MIN_ZONE_SIZE_PERC + 2*m_pr_params->base_ds_increment) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done); 
			return;
		}
		
		double perc = (m_ds_perc -
			m_pr_params->base_ds_increment) / 100.0;

		if (ui->horizontalSlider_p_on->value() == 0) {
			QMessageBox::information(this, m_str_warning, 
				" P_on zero, " + m_str_operation_cannot_be_done);
			return;
		}
		else {
			double delta = (1.0 - std::pow(perc, (1.0 / 3.0)));
			double value = m_pr_params->p_on_default - m_pr_params->p_on_default  * delta; 

			updatePonSetPoint(value);
		}

		if (ui->horizontalSlider_recirculation->value() == 0) {
			updateVrecircSetPoint(-3.0);
		}
		else {
			double delta = (1.0 - std::pow(perc, (1.0 / 3.0)));
			double value = -m_pr_params->v_recirc_default - m_pr_params->v_recirc_default * delta;

			updateVrecircSetPoint(value);
		}
		updateFlowControlPercentages();

	}
}

void Labonatip_GUI::flowSpeedPlus() {

	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::flowSpeedPlus    " << endl;

	// +percentage to all values
	// Poff does not read too low values, 
	// if 5% different is less than 5 mbar .... start -> start + 5 --> start - 5%
	if (m_pipette_active) {
		bool success = false;
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeFlowspeedBy(m_pr_params->base_fs_increment);
		}
		else{
			success = m_ppc1->setFlowspeed(m_fs_perc +
				m_pr_params->base_fs_increment);
		}

		if (!success) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}
		else
		{
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();
			m_pipette_status->v_switch_set_point = -m_ppc1->getVswitchSetPoint();
			m_pipette_status->poff_set_point = m_ppc1->getPoffSetPoint();
			m_pipette_status->pon_set_point = m_ppc1->getPonSetPoint();

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);
			ui->horizontalSlider_switch->blockSignals(true);
			ui->horizontalSlider_switch->setValue(m_pipette_status->v_switch_set_point);
			ui->horizontalSlider_switch->blockSignals(false);
			ui->horizontalSlider_p_off->blockSignals(true);
			ui->horizontalSlider_p_off->setValue(m_pipette_status->poff_set_point);
			ui->horizontalSlider_p_off->blockSignals(false);
			ui->horizontalSlider_p_on->blockSignals(true);
			ui->horizontalSlider_p_on->setValue(m_pipette_status->pon_set_point);
			ui->horizontalSlider_p_on->blockSignals(false);
		}
	}
	if (m_simulationOnly) {

		if (m_fs_perc > MAX_FLOW_SPEED_PERC - m_pr_params->base_fs_increment) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done); 
			return;
		}

		if (ui->horizontalSlider_p_on->value() == 0) {
			updatePonSetPoint(5.0);
		}
		else {
			double value = m_pipette_status->pon_set_point +
				m_pr_params->p_on_default *  m_pr_params->base_fs_increment / 100.0;
			updatePonSetPoint(value);
		}

		if (ui->horizontalSlider_p_off->value() == 0) {
			updatePoffSetPoint(5.0);
		}
		else {
			double value = m_pipette_status->poff_set_point +
				m_pr_params->p_off_default * m_pr_params->base_fs_increment / 100.0;
			updatePoffSetPoint(value);
		}

		if (ui->horizontalSlider_switch->value() == 0) {
			updateVswitchSetPoint ( 5.0 );
		}
		else {
			double value = m_pipette_status->v_switch_set_point -
				m_pr_params->v_switch_default * m_pr_params->base_fs_increment / 100.0;
			updateVswitchSetPoint(value);
		}

		if (ui->horizontalSlider_recirculation->value() == 0) {
			updateVrecircSetPoint(5.0);
		}
		else {
			double value = m_pipette_status->v_recirc_set_point -
				m_pr_params->v_recirc_default * m_pr_params->base_fs_increment / 100.0;
			updateVrecircSetPoint(value);
		}
		updateFlowControlPercentages();

	}
}

void Labonatip_GUI::flowSpeedMinus() {


	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::flowSpeedMinus    " << endl;

	// -percentage to all values
	if (m_pipette_active) {
		bool success = false;
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeFlowspeedBy(-m_pr_params->base_fs_increment);
		}
		else {
			success = m_ppc1->setFlowspeed(m_fs_perc -
				m_pr_params->base_fs_increment);
		}

		if (!success) {
				QMessageBox::information(this, m_str_warning, 
					m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}
		else
		{
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();
			m_pipette_status->v_switch_set_point = -m_ppc1->getVswitchSetPoint();
			m_pipette_status->poff_set_point = m_ppc1->getPoffSetPoint();
			m_pipette_status->pon_set_point = m_ppc1->getPonSetPoint();

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);
			ui->horizontalSlider_switch->blockSignals(true);
			ui->horizontalSlider_switch->setValue(m_pipette_status->v_switch_set_point);
			ui->horizontalSlider_switch->blockSignals(false);
			ui->horizontalSlider_p_off->blockSignals(true);
			ui->horizontalSlider_p_off->setValue(m_pipette_status->poff_set_point);
			ui->horizontalSlider_p_off->blockSignals(false);
			ui->horizontalSlider_p_on->blockSignals(true);
			ui->horizontalSlider_p_on->setValue(m_pipette_status->pon_set_point);
			ui->horizontalSlider_p_on->blockSignals(false);
		}
	}
	if (m_simulationOnly) {
		
		if (m_fs_perc < MIN_FLOW_SPEED_PERC + m_pr_params->base_fs_increment) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done); 
			return;
		}

		double value = m_pipette_status->pon_set_point - 
			m_pr_params->p_on_default * m_pr_params->base_fs_increment / 100.0;
		updatePonSetPoint(value);
		value = m_pipette_status->poff_set_point - 
			m_pr_params->p_off_default * m_pr_params->base_fs_increment / 100.0;
		updatePoffSetPoint(value);
		value = m_pipette_status->v_switch_set_point + 
			m_pr_params->v_switch_default * m_pr_params->base_fs_increment / 100.0;
		updateVswitchSetPoint(value);
		value = m_pipette_status->v_recirc_set_point + 
			m_pr_params->v_recirc_default * m_pr_params->base_fs_increment / 100.0;
		updateVrecircSetPoint(value);

		updateFlowControlPercentages();
	}
}

void Labonatip_GUI::vacuumPlus() {

	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::vacuumPlus    " << endl;

	// +percentage to v_recirculation
	if (m_pipette_active) {
		bool success = false;
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeVacuumPercentageBy(m_pr_params->base_v_increment);
		}
		else {
			success = m_ppc1->setVacuumPercentage(m_v_perc + //ui->lcdNumber_vacuum_percentage->value() +
				m_pr_params->base_v_increment);
		}

		if (!success) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}
		else {
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);
		}
	}
	if (m_simulationOnly) {

		if (m_v_perc > MAX_VACUUM_PERC - m_pr_params->base_v_increment) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done); 
			return;
		}

		if (ui->horizontalSlider_recirculation->value() == 0) {
			ui->horizontalSlider_recirculation->setValue(5);
		}
		else {

			double value = m_pipette_status->v_recirc_set_point - m_pr_params->v_recirc_default * m_pr_params->base_v_increment / 100.0;
			cout << "Labonatip_GUI::vacuumPlus    ::: new recirculation value " << value << endl;
			updateVrecircSetPoint(value);
			
		}

		updateFlowControlPercentages();
	}
}

void Labonatip_GUI::vacuumMinus() {

	cout << QDate::currentDate().toString().toStdString() << "  " 
		 << QTime::currentTime().toString().toStdString() << "  "
		 << "Labonatip_GUI::vacuumMinus    " << endl;

	// -5% v_recirculation
	if (m_pipette_active) {
		bool success = false; 
		if (m_pr_params->useDefValSetPoint)
		{
			success = m_ppc1->changeVacuumPercentageBy(-m_pr_params->base_v_increment);
		}
		else {
			success = m_ppc1->setVacuumPercentage(m_v_perc - //ui->lcdNumber_vacuum_percentage->value() -
				m_pr_params->base_v_increment);
		}

		if (!success) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}
		else {
			// update the set point
			m_pipette_status->v_recirc_set_point = -m_ppc1->getVrecircSetPoint();
			//ui->label_recircPressure->setText(QString(QString::number(m_v_recirc_set_point) + " mbar"));

			// update the slider for the GUI
			ui->horizontalSlider_recirculation->blockSignals(true);
			ui->horizontalSlider_recirculation->setValue(m_pipette_status->v_recirc_set_point);
			ui->horizontalSlider_recirculation->blockSignals(false);

		}
	}
	if (m_simulationOnly) {

		if (m_v_perc < MIN_VACUUM_PERC + m_pr_params->base_v_increment) {
			QMessageBox::information(this, m_str_warning, 
				m_str_operation_cannot_be_done); 
			return;
		}

		if (ui->horizontalSlider_recirculation->value() == 0) {
			QMessageBox::information(this, m_str_warning,
				m_str_operation_cannot_be_done + "<br>" + m_str_out_of_bound);
		}

		double value = m_pipette_status->v_recirc_set_point + m_pr_params->v_recirc_default * m_pr_params->base_v_increment / 100.0;
		cout << "Labonatip_GUI::vacuumMinus    ::: new recirculation value " << value << endl;
		updateVrecircSetPoint(value);

		updateFlowControlPercentages();
	}
}

void Labonatip_GUI::updateFlowControlPercentages()
{
	updateFlows();
	if (m_simulationOnly) {

		// calculate droplet size percentage
		m_ds_perc = 100.0*(m_pipette_status->in_out_ratio_on + 0.21) / 0.31;
		if (m_ds_perc < 0) {
			ui->lcdNumber_dropletSize_percentage->display("A");
		}
		else {
			ui->lcdNumber_dropletSize_percentage->display(m_ds_perc);
		}
		
		// calculate flow speed percentage
		double ponp = 100.0 * m_pipette_status->pon_set_point / m_pr_params->p_on_default;

		//MB: mod to consider pon only in the calculation of the speed
		m_fs_perc = ponp;
		ui->lcdNumber_flowspeed_percentage->display(m_fs_perc);

		//calculate vacuum percentage
		m_v_perc = 100.0 * m_pipette_status->v_recirc_set_point / (-m_pr_params->v_recirc_default);
		ui->lcdNumber_vacuum_percentage->display(m_v_perc);

	}
}